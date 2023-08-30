#include "ledCalibrationController.h"
#include "permissions.h"
#include "message/calibration.interface.h"
#include "calibrationChangeEntry.h"
#include "ledChannel.h"


#include <QFutureWatcher>
#include <QtConcurrentRun>
#include <QTimer>

#include <precitec/userManagement.h>
#include <precitec/userLog.h>
#include <common/systemConfiguration.h>
#include <viWeldHead/WeldingHeadControl.h>
#include "viWeldHead/LEDControl/LEDI_ExportedDatatypes.hpp"

using namespace precitec::interface;
using precitec::gui::components::userLog::UserLog;
using precitec::gui::components::user::UserManagement;

namespace precitec
{
namespace gui
{

namespace
{

enum CameraInterfaceType
{
    FrameGrabber,
    GigE
};
    
template <typename T>
T getValue(const Configuration &configuration, const std::string &key, T defaultValue)
{
    auto it = std::find_if(configuration.begin(), configuration.end(), [key] (auto kv) { return kv->key() == key; });
    if (it == configuration.end())
    {
        return defaultValue;
    }
    return (*it)->template value<T>();
}

}

LEDCalibrationController::LEDCalibrationController(QObject *parent)
    : QAbstractListModel(parent)
    , m_ledCalibrationTimeout(new QTimer(this))
{
    m_ledCalibrationTimeout->setSingleShot(true);
    m_ledCalibrationTimeout->setInterval(std::chrono::seconds{30});
    m_cameraInterfaceType = interface::SystemConfiguration::instance().get(interface::SystemConfiguration::IntKey::CameraInterfaceType);
    
    connect(m_ledCalibrationTimeout, &QTimer::timeout, this, &LEDCalibrationController::endLEDCalibration);
    
    connect(this, &LEDCalibrationController::weldHeadDeviceChanged, this,
            [this]
            {
                if (!m_weldHeadDevice)
                {
                    setWeldHeadReady(false);
                    return;
                }
                auto weldHeadDevice = m_weldHeadDevice;
                if (!UserManagement::instance()->hasPermission(int(weldHeadDevice->readPermission())))
                {
                    return;
                }
                auto watcher = new QFutureWatcher<Configuration>{this};
                connect(watcher, &QFutureWatcher<Configuration>::finished, this,
                        [this, weldHeadDevice, watcher]
                        {
                            watcher->deleteLater();
                            auto configuration = watcher->result();

                            m_ledType = weldHeadDevice->deviceProxy()->get(std::string("LED_CONTROLLER_TYPE"), 0)->value<int>();
                            emit ledTypeChanged();

                            
                            std::string refStr;
                           
                            for(int i = 0; i< m_ledType; i++)
                            {
                                refStr = "LEDPanel" + std::to_string(i+1) + "Intensity";
                                m_channels.at(i)->setIntensity(getValue(configuration, std::string(refStr), 50));                                 
                            }    


                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel1OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel2OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel3OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel4OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel5OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel6OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel7OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel8OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LineLaser1OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LineLaser2OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("FieldLight1OnOff"), false)));
                            weldHeadDevice->setKeyValue(SmpKeyValue{new TKeyValue<bool>{std::string{"LEDSendData"}, true}});

                            turnLEDChannelsOff();

                            setWeldHeadReady(true);
                        }
                );
                watcher->setFuture(QtConcurrent::run(
                    [weldHeadDevice]
                    {
                        return weldHeadDevice->deviceProxy()->get();
                    }));
            }
    );

    

    connect(this, &LEDCalibrationController::serviceReadyChanged, this, &LEDCalibrationController::initCurrentValues);
    connect(this, &LEDCalibrationController::weldHeadReadyChanged, this, &LEDCalibrationController::initCurrentValues);
    connect(this, &LEDCalibrationController::calibrationReadyChanged, this, &LEDCalibrationController::setCameraBrightness);
    connect(this, &LEDCalibrationController::grabberReadyChanged, this, &LEDCalibrationController::setCameraBrightness);

    connect(this, &LEDCalibrationController::updatingChanged, this, &LEDCalibrationController::startLEDCalibration);
    connect(this, &LEDCalibrationController::ledTypeChanged, this, &LEDCalibrationController::updateVisible);

    connect(this, &LEDCalibrationController::calibrationDeviceChanged, this,
            [this]
            {
                if (!m_calibrationDevice)
                {
                    setCalibrationReady(false);
                    return;
                }
                auto calibrationDevice = m_calibrationDevice;

                if (!UserManagement::instance()->hasPermission(int(calibrationDevice->readPermission())))
                {
                    return;
                }
                auto watcher = new QFutureWatcher<Configuration>{this};
                connect(watcher, &QFutureWatcher<Configuration>::finished, this,
                        [this, calibrationDevice, watcher]
                        {
                            watcher->deleteLater();
                            auto configuration = watcher->result();

                            std::string refStr;
                            std::string measStr;
                            for(int i = 0; i< m_ledType; i++)
                            {
                                 refStr = "ledChannel" + std::to_string(i+1) + "ReferenceBrightness";
                                 measStr = "ledChannel" + std::to_string(i+1) + "MeasuredBrightness";
                                 m_channels.at(i)->setReferenceBrightness(getValue(configuration, refStr, 125));
                                 m_channels.at(i)->setMeasuredBrightness(getValue(configuration, measStr, 0));
                            }            

                            m_blackLevelShift = getValue(configuration, std::string("CameraBlackLevelShiftForLEDcalib"), -100);

                            calibrationDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(std::string("ledCalibrationChannel"), 0)));

                            setCalibrationReady(true);
                        }
                );
                watcher->setFuture(QtConcurrent::run(
                    [calibrationDevice]
                    {
                        return calibrationDevice->deviceProxy()->get();
                    }));
            }
    );
    connect(this, &LEDCalibrationController::serviceDeviceChanged, this,
            [this]
            {
                if (!m_serviceDevice)
                {
                    setServiceReady(false);
                    return;
                }
                auto serviceDevice = m_serviceDevice;
                if (!UserManagement::instance()->hasPermission(int(serviceDevice->readPermission())))
                {
                    return;
                }
                auto watcher = new QFutureWatcher<Configuration>{this};
                connect(watcher, &QFutureWatcher<Configuration>::finished, this,
                        [this, watcher]
                        {
                            watcher->deleteLater();
                            auto configuration = watcher->result();
                            
                            std::string refStr;
                           
                            for(int i = 0; i< m_ledType; i++)
                            {
                                refStr = "LED_MaxCurrent_mA_Chan" + std::to_string(i+1) ;
                                m_channels.at(i)->setMaxCurrent(getValue(configuration, std::string(refStr), 1500));                                 
                            }    
                           

                            setServiceReady(true);
                        }
                );
                watcher->setFuture(QtConcurrent::run(
                    [serviceDevice]
                    {
                        return serviceDevice->deviceProxy()->get();
                    }));
            }
    );
    
    connect(this, &LEDCalibrationController::grabberDeviceChanged, this,
            [this]
            {
                if (!m_grabberDevice)
                {
                    setGrabberReady(false);
                    return;
                }
                auto grabberDevice = m_grabberDevice;
                if (!UserManagement::instance()->hasPermission(int(grabberDevice->readPermission())))
                {
                    return;
                }
                if (!hasGrabberPermission())
                {
                    return;
                }
                auto watcher = new QFutureWatcher<Configuration>{this};
                connect(watcher, &QFutureWatcher<Configuration>::finished, this,
                        [this, grabberDevice, watcher]
                        {
                            watcher->deleteLater();
                            auto configuration = watcher->result();

                            m_zeroAdjustment = getValue(configuration, std::string("BlackLevelOffset"), 3300);
                            
                            grabberDevice->setKeyValue(SmpKeyValue(new TKeyValue<float>(std::string("ExposureTime"), 0.5f)));
                            if(m_cameraInterfaceType == CameraInterfaceType::FrameGrabber)
                            {                              
                                grabberDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(std::string("LinLog.Mode"), 0)));
                                grabberDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(std::string("PWM.PWM1"), 0)));
                                grabberDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(std::string("PWM.PWM2"), 0)));
                                grabberDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(std::string("PWM.PWMBel"), 0)));
                            }

                            setGrabberReady(true);
                        }
                );
                watcher->setFuture(QtConcurrent::run(
                    [grabberDevice]
                    {
                        return grabberDevice->deviceProxy()->get();
                    }));
            }
    );
    
    for (auto i = 0; i < m_ledType; ++i)
    {
        m_channels.emplace_back(new LEDChannel(this));
        const QModelIndex idx = index(i);
        connect(m_channels.at(i), &LEDChannel::enabledChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole});
        });
        connect(m_channels.at(i), &LEDChannel::minCurrentChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole + 1});
        });
        connect(m_channels.at(i), &LEDChannel::maxCurrentChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole + 2});
        });
        connect(m_channels.at(i), &LEDChannel::referenceBrightnessChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole + 3});
        });
        connect(m_channels.at(i), &LEDChannel::measuredBrightnessChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole + 4});
        });
        connect(m_channels.at(i), &LEDChannel::currentValueChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole + 5});
        });
        connect(m_channels.at(i), &LEDChannel::originalValueChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole + 6});
        });
        connect(m_channels.at(i), &LEDChannel::intensityChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole + 7});
        });
         connect(m_channels.at(i), &LEDChannel::visibleChanged, this, [this, idx]
        {
            emit dataChanged(idx, idx, {Qt::UserRole + 8});
        });
    }
}

LEDCalibrationController::~LEDCalibrationController() = default;

QHash<int, QByteArray> LEDCalibrationController::roleNames() const
{
    return {
        {Qt::DisplayRole, QByteArrayLiteral("channel")},
        {Qt::UserRole, QByteArrayLiteral("enabled")},
        {Qt::UserRole + 1, QByteArrayLiteral("minCurrent")},
        {Qt::UserRole + 2, QByteArrayLiteral("maxCurrent")},
        {Qt::UserRole + 3, QByteArrayLiteral("referenceBrightness")},
        {Qt::UserRole + 4, QByteArrayLiteral("measuredBrightness")},
        {Qt::UserRole + 5, QByteArrayLiteral("currentValue")},
        {Qt::UserRole + 6, QByteArrayLiteral("originalValue")},
        {Qt::UserRole + 7, QByteArrayLiteral("intensity")},
        {Qt::UserRole + 8, QByteArrayLiteral("visible")}
    };
}

QVariant LEDCalibrationController::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant{};
    }
    if (role == Qt::DisplayRole)
    {
        return QVariant::fromValue(m_channels.at(index.row()));
    }
    if (role == Qt::UserRole)
    {
        return m_channels.at(index.row())->enabled();
    }
    if (role == Qt::UserRole + 1)
    {
        return m_channels.at(index.row())->minCurrent();
    }
    if (role == Qt::UserRole + 2)
    {
        return m_channels.at(index.row())->maxCurrent();
    }
    if (role == Qt::UserRole + 3)
    {
        return m_channels.at(index.row())->referenceBrightness();
    }
    if (role == Qt::UserRole + 4)
    {
        return m_channels.at(index.row())->measuredBrightness();
    }
    if (role == Qt::UserRole + 5)
    {
        return m_channels.at(index.row())->currentValue();
    }
    if (role == Qt::UserRole + 6)
    {
        return m_channels.at(index.row())->originalValue();
    }
    if (role == Qt::UserRole + 7)
    {
        return m_channels.at(index.row())->intensity();
    }
    if (role == Qt::UserRole + 8)
    {
        return m_channels.at(index.row())->visible();
    }

    return QVariant{};
}

int LEDCalibrationController::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return m_channels.size();
}

void LEDCalibrationController::initCurrentValues()
{
    if (!isServiceReady())
    {
        return;
    }
    if (!isWeldHeadReady())
    {
        return;
    }

   for(auto i = 0; i < m_ledType; i++)
   {        
      m_channels.at(i)->setIntensityToValue();
      m_channels.at(i)->setOriginalValue(m_channels.at(i)->currentValue());
   }

      
}

void LEDCalibrationController::setCameraBrightness()
{
    if (!m_grabberDevice)
    {
        return;
    }
    if (!UserManagement::instance()->hasPermission(int(m_grabberDevice->readPermission())))
    {
        return;
    }
    if (!hasGrabberPermission())
    {
        return;
    }
    if (!isGrabberReady())
    {
        return;
    }
    if (!isCalibrationReady())
    {
        return;
    }
    if (isGrabberUpdating())
    {
        return;
    }
    setGrabberUpdating(true);

    auto watcher = new QFutureWatcher<Configuration>{this};
    const auto grabberDevice = m_grabberDevice;
    connect(watcher, &QFutureWatcher<void>::finished, this,
            [this, watcher, grabberDevice]
            {
                watcher->deleteLater();
                auto configuration = watcher->result();

                grabberDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(std::string("Voltages.BlackLevelOffset"), m_zeroAdjustment + m_blackLevelShift)));

                setGrabberUpdating(false);
            }
    );
    watcher->setFuture(QtConcurrent::run(
        [grabberDevice]
        {
            return grabberDevice->deviceProxy()->get();
        }));
}

void LEDCalibrationController::loadCalibrationResults()
{
    if (!m_calibrationDevice)
    {
        return;
    }
    if (!UserManagement::instance()->hasPermission(int(m_calibrationDevice->readPermission())))
    {
        return;
    }
    if (!isCalibrationReady())
    {
        return;
    }
    if (isCalibrationUpdating())
    {
        return;
    }
    setCalibrationUpdating(true);

    auto watcher = new QFutureWatcher<Configuration>{this};
    connect(watcher, &QFutureWatcher<void>::finished, this,
            [this, watcher]
            {
                watcher->deleteLater();
                auto configuration = watcher->result();

                if(m_ledType == LEDControllerType::eLEDTypePP820)
                {                    
                    m_channels.at(0)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel1MeasuredBrightness"), 0));
                    m_channels.at(1)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel2MeasuredBrightness"), 0));
                    m_channels.at(2)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel3MeasuredBrightness"), 0));
                    m_channels.at(3)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel4MeasuredBrightness"), 0));
                    m_channels.at(4)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel5MeasuredBrightness"), 0));
                    m_channels.at(5)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel6MeasuredBrightness"), 0));
                    m_channels.at(6)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel7MeasuredBrightness"), 0));
                    m_channels.at(7)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel8MeasuredBrightness"), 0));
                }
                else
                {
                    m_channels.at(0)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel1MeasuredBrightness"), 0));
                    m_channels.at(1)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel2MeasuredBrightness"), 0));
                    m_channels.at(2)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel3MeasuredBrightness"), 0));
                    m_channels.at(3)->setMeasuredBrightness(getValue(configuration, std::string("ledChannel4MeasuredBrightness"), 0));
                }
                    

                setCalibrationUpdating(false);
            }
    );
    const auto calibrationDevice = m_calibrationDevice;
    watcher->setFuture(QtConcurrent::run(
        [calibrationDevice]
        {
            return calibrationDevice->deviceProxy()->get();
        }));
}

void LEDCalibrationController::updateEnabled(int index, bool enabled)
{
    if (m_channels.at(index)->enabled() == enabled)
    {
        return;
    }

    turnLEDChannelsOff();
    m_channels.at(index)->setEnabled(enabled);

    QString key = QStringLiteral("LEDPanel") + QString::number(index + 1) + QStringLiteral("OnOff");

    const auto weldHeadDevice = m_weldHeadDevice;
    updateWeldHeadDevice([weldHeadDevice, key, enabled]
    {
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel1OnOff"), false)));
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel2OnOff"), false)));
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel3OnOff"), false)));
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel4OnOff"), false)));
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel5OnOff"), false)));
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel6OnOff"), false)));
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel7OnOff"), false)));
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(std::string("LEDPanel8OnOff"), false)));

        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<bool>(key.toStdString(), enabled)));
        weldHeadDevice->setKeyValue(SmpKeyValue{new TKeyValue<bool>{std::string{"LEDSendData"}, true}});
    });
    const auto calibrationDevice = m_calibrationDevice;
    updateCalibrationDevice([calibrationDevice, index, enabled]
    {
        if(enabled)
        {
            calibrationDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(std::string("ledCalibrationChannel"), index + 1)));
        }
        else
        {
            calibrationDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(std::string("ledCalibrationChannel"), 0)));
        }
    });
}

void LEDCalibrationController::updateCurrentValue(int index, int currentValue)
{
    if (m_channels.at(index)->currentValue() == currentValue)
    {
        return;
    }
    m_channels.at(index)->setCurrentValue(currentValue);

    const int intensity = m_channels.at(index)->normalizedIntensity(currentValue);

    QString key = QStringLiteral("LEDPanel") + QString::number(index + 1) + QStringLiteral("Intensity");

    const auto weldHeadDevice = m_weldHeadDevice;
    updateWeldHeadDevice([weldHeadDevice, key, intensity]
    {
        weldHeadDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(key.toStdString(), intensity)));
        weldHeadDevice->setKeyValue(SmpKeyValue{new TKeyValue<bool>{std::string{"LEDSendData"}, true}});
    });
}

void LEDCalibrationController::updateReferenceBrightness(int index, int currentValue)
{
    if (m_channels.at(index)->referenceBrightness() == currentValue)
    {
        return;
    }
    m_channels.at(index)->setReferenceBrightness(currentValue);

    QString key = QStringLiteral("ledChannel") + QString::number(index + 1) + QStringLiteral("ReferenceBrightness");

    const auto calibrationDevice = m_calibrationDevice;
    updateCalibrationDevice([calibrationDevice, key, currentValue]
    {
        calibrationDevice->setKeyValue(SmpKeyValue(new TKeyValue<int>(key.toStdString(), currentValue)));
    });
}

void LEDCalibrationController::setInspectionCmdProxy(const InspectionCmdProxy &proxy)
{
    if (m_inspectionCmdProxy == proxy)
    {
        return;
    }
    m_inspectionCmdProxy = proxy;
    emit inspectionCmdProxyChanged();
}

void LEDCalibrationController::setCalibrationDevice(DeviceProxyWrapper *device)
{
    if (m_calibrationDevice == device)
    {
        return;
    }
    disconnect(m_calibrationDeviceDestroyed);
    m_calibrationDevice = device;
    if (m_calibrationDevice)
    {
        m_calibrationDeviceDestroyed = connect(device, &DeviceProxyWrapper::destroyed, this, std::bind(&LEDCalibrationController::setCalibrationDevice, this, nullptr));
    } else
    {
        m_calibrationDeviceDestroyed = {};
    }
    emit calibrationDeviceChanged();
}

void LEDCalibrationController::setServiceDevice(DeviceProxyWrapper *device)
{
    if (m_serviceDevice == device)
    {
        return;
    }
    disconnect(m_serviceDeviceDestroyed);
    m_serviceDevice = device;
    if (m_serviceDevice)
    {
        m_serviceDeviceDestroyed = connect(device, &DeviceProxyWrapper::destroyed, this, std::bind(&LEDCalibrationController::setServiceDevice, this, nullptr));
    } else
    {
        m_serviceDeviceDestroyed = {};
    }
    emit serviceDeviceChanged();
}

void LEDCalibrationController::setWeldHeadDevice(DeviceProxyWrapper *device)
{
    if (m_weldHeadDevice == device)
    {
        return;
    }
    disconnect(m_weldHeadDeviceDestroyed);
    m_weldHeadDevice = device;
    if (m_weldHeadDevice)
    {
        m_weldHeadDeviceDestroyed = connect(device, &DeviceProxyWrapper::destroyed, this, std::bind(&LEDCalibrationController::setWeldHeadDevice, this, nullptr));
    } else
    {
        m_weldHeadDeviceDestroyed = {};
    }
    emit weldHeadDeviceChanged();
}

void LEDCalibrationController::setGrabberDevice(DeviceProxyWrapper *device)
{
    if (m_grabberDevice == device)
    {
        return;
    }
    disconnect(m_grabberDeviceDestroyed);
    m_grabberDevice = device;
    if (m_grabberDevice)
    {
        m_grabberDeviceDestroyed = connect(device, &DeviceProxyWrapper::destroyed, this, std::bind(&LEDCalibrationController::setGrabberDevice, this, nullptr));
    } else
    {
        m_grabberDeviceDestroyed = {};
    }
    emit grabberDeviceChanged();
}

void LEDCalibrationController::startLEDCalibration()
{
    if (!m_active)
    {
        return;
    }
    if (!inspectionCmdProxy())
    {
        return;
    }
    if (isCalibrating())
    {
        return;
    }
    if (isCalibrationUpdating())
    {
        return;
    }
    if (isWeldHeadUpdating())
    {
        return;
    }
    if (isGrabberUpdating())
    {
        return;
    }
    if (!hasLEDEnabled())
    {
        return;
    }

    setCalibrating(true);
    QtConcurrent::run(inspectionCmdProxy().get(), &precitec::interface::TInspectionCmd<precitec::interface::EventProxy>::requestCalibration, int(precitec::interface::eCalibrateLED));
    m_ledCalibrationTimeout->start();
    UserLog::instance()->addChange(new CalibrationChangeEntry(CalibrationType::LED));
}

void LEDCalibrationController::endLEDCalibration()
{
    if (!isCalibrating())
    {
        return;
    }
    m_ledCalibrationTimeout->stop();
    loadCalibrationResults();
    setCalibrating(false);
    startLEDCalibration();
}

void LEDCalibrationController::setCalibrating(bool set)
{
    if (m_calibrating == set)
    {
        return;
    }
    m_calibrating = set;
    emit calibratingChanged();
}

void LEDCalibrationController::setCalibrationReady(bool set)
{
    if (m_calibrationReady == set)
    {
        return;
    }
    m_calibrationReady = set;
    emit calibrationReadyChanged();
}

void LEDCalibrationController::setServiceReady(bool set)
{
    if (m_serviceReady == set)
    {
        return;
    }
    m_serviceReady = set;
    emit serviceReadyChanged();
}

void LEDCalibrationController::setWeldHeadReady(bool set)
{
    if (m_weldHeadReady == set)
    {
        return;
    }
    m_weldHeadReady = set;
    emit weldHeadReadyChanged();
}

void LEDCalibrationController::setGrabberReady(bool set)
{
    if (m_grabberReady == set)
    {
        return;
    }
    m_grabberReady = set;
    emit grabberDeviceChanged();
}

void LEDCalibrationController::setCalibrationUpdating(bool set)
{
    if (m_calibrationUpdating == set)
    {
        return;
    }
    m_calibrationUpdating = set;
    emit updatingChanged();
}

void LEDCalibrationController::setWeldHeadUpdating(bool set)
{
    if (m_weldHeadUpdating == set)
    {
        return;
    }
    m_weldHeadUpdating = set;
    emit updatingChanged();
}

void LEDCalibrationController::setGrabberUpdating(bool set)
{
    if (m_grabberUpdating == set)
    {
        return;
    }
    m_grabberUpdating = set;
    emit updatingChanged();
}

void LEDCalibrationController::setActive(bool set)
{
    if (m_active == set)
    {
        return;
    }
    m_active = set;

    if (!m_active)
    {
        endLEDCalibration();
    }
    emit activeChanged();
}

void LEDCalibrationController::updateCalibrationDevice(std::function<void()> updateFunction)
{
    if (!m_calibrationDevice)
    {
        return;
    }
    if (!hasCalibrationPermission())
    {
        return;
    }
    if (!isCalibrationReady())
    {
        return;
    }
    if (isCalibrationUpdating())
    {
        return;
    }
    setCalibrationUpdating(true);

    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, this,
            [this, watcher]
            {
                watcher->deleteLater();
                setCalibrationUpdating(false);
            }
    );
    watcher->setFuture(QtConcurrent::run(updateFunction));
}

void LEDCalibrationController::updateWeldHeadDevice(std::function<void()> updateFunction)
{
    if (!m_weldHeadDevice)
    {
        return;
    }
    if (!hasWeldHeadPermission())
    {
        return;
    }
    if (!isWeldHeadReady())
    {
        return;
    }
    if (isWeldHeadUpdating())
    {
        return;
    }
    setWeldHeadUpdating(true);

    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, this,
            [this, watcher]
            {
                watcher->deleteLater();
                setWeldHeadUpdating(false);
            }
    );
    watcher->setFuture(QtConcurrent::run(updateFunction));
}

void LEDCalibrationController::updateGrabberDevice(std::function<void()> updateFunction)
{
    if (!m_grabberDevice)
    {
        return;
    }
    if (!hasGrabberPermission())
    {
        return;
    }
    if (!isGrabberReady())
    {
        return;
    }
    if (isGrabberUpdating())
    {
        return;
    }
    setGrabberUpdating(true);

    QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
    connect(watcher, &QFutureWatcher<void>::finished, this,
            [this, watcher]
            {
                watcher->deleteLater();
                setGrabberUpdating(false);
            }
    );
    watcher->setFuture(QtConcurrent::run(updateFunction));
}

bool LEDCalibrationController::hasCalibrationPermission()
{
    if (!UserManagement::instance()->hasPermission(int(m_calibrationDevice->writePermission())))
    {
        return false;
    }
    if (!UserManagement::instance()->hasPermission(int(Permission::EditCalibrationDeviceConfig)))
    {
        return false;
    }
    return true;
}

bool LEDCalibrationController::hasGrabberPermission()
{
    if (!UserManagement::instance()->hasPermission(int(m_grabberDevice->writePermission())))
    {
        return false;
    }
    if (!UserManagement::instance()->hasPermission(int(Permission::EditGrabberDeviceConfig)))
    {
        return false;
    }
    return true;
}

bool LEDCalibrationController::hasWeldHeadPermission()
{
    if (!UserManagement::instance()->hasPermission(int(m_weldHeadDevice->writePermission())))
    {
        return false;
    }
    if (!UserManagement::instance()->hasPermission(int(Permission::EditWeldHeadDeviceConfig)))
    {
        return false;
    }
    return true;
}

void LEDCalibrationController::turnLEDChannelsOff()
{
    for (auto i = 0u; i < m_channels.size(); ++i)
    {
        m_channels.at(i)->setEnabled(false);
    }
}

bool LEDCalibrationController::hasLEDEnabled()
{
    auto hasEnabled = false;
    for (auto i = 0u; i < m_channels.size(); ++i)
    {
        if (m_channels.at(i)->enabled())
        {
            hasEnabled = true;
            break;
        }
    }
    return hasEnabled;
}

void LEDCalibrationController::updateVisible()
{
    if (m_channels.size() != 4)
    {
        return;
    }
    m_channels.at(0)->setVisible(m_ledType >= 1);
    m_channels.at(1)->setVisible(m_ledType >= 1 || m_ledType == 2);
    m_channels.at(2)->setVisible(m_ledType == 1);
    m_channels.at(3)->setVisible(m_ledType == 1);
}

}
}


