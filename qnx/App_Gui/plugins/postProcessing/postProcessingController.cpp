

#include "../../App_Storage/src/compatibility.h"

#include "message/simulationCmd.handler.h"
#include "message/simulationCmd.proxy.h"
#include "event/storageUpdate.interface.h"

#include "./../Mod_Storage/src/abstractMeasureTask.h"
#include "./../Mod_Storage/src/attribute.h"
#include "./../Mod_Storage/src/parameter.h"
#include "./../Mod_Storage/src/parameterSet.h"
#include "./../Mod_Storage/src/product.h"
#include "./../Mod_Storage/src/productModel.h"
#include "../App_Gui/src/productModifiedChangeEntry.h"
#include "./../Mod_Storage/src/seam.h"
#include "./../Mod_Storage/src/seamInterval.h"
#include "./../Mod_Storage/src/subGraphModel.h"
#include "./../Mod_Storage/src/graphFunctions.h"
#include "./../Mod_Storage/src/graphModel.h"

#include <precitec/userLog.h>

#include <QFutureWatcher>
#include <QtConcurrentRun>
#include <QTimer>

#include "postProcessingController.h"
#include <../Mod_Storage/src/graphFunctions.h>
#include <../Mod_Storage/src/parameterSet.h>
#include "../App_Gui/src/simulationController.h"

using namespace precitec::interface;
using namespace precitec::storage::compatibility;

using precitec::storage::graphFunctions::getCurrentGraphId;
using precitec::storage::graphFunctions::getGraphFromModel;
using precitec::gui::components::userLog::UserLog;

namespace precitec
{
namespace gui
{
namespace components
{
namespace postprocessing
{
    
PostProcessingController::PostProcessingController(QObject *parent)
    : QObject(parent)    
{
   connect(this, &PostProcessingController::productInstanceChanged, this,
        [this]
        {
            const auto index = m_productInstance.fileName().lastIndexOf(QLatin1String("-SN-"));
            if (index == -1)
            {
                m_productInstanceId = Poco::UUID{};
            } else
            {
                m_productInstanceId = Poco::UUID{m_productInstance.fileName().left(index).toStdString()};
            }
            emit serialNumberChanged();
        }
    );
    connect(this, &PostProcessingController::serialNumberChanged, this,
        [this]
        {
            if (!m_simulationCmdProxy)
            {
                return;
            }
            QFutureWatcher<SimulationInitStatus> *watcher = new QFutureWatcher<SimulationInitStatus>();
            connect(watcher, &QFutureWatcher<SimulationInitStatus>::finished, this,
                [this, watcher]
                {
                    watcher->deleteLater();
                    auto status = watcher->result();
                    m_pathModel->init(QString::fromStdString(status.imageBasePath()), status.imageData());

                    emit imageChanged();

                    m_loading = false;
                    emit loadingChanged();
                }
            );
            m_loading = true;
            emit loadingChanged();
            auto future = QtConcurrent::run(m_simulationCmdProxy.get(), &SimulationCmdProxy::element_type::initSimulation, toPoco(m_product), m_productInstanceId, toPoco(m_dataProduct));
            watcher->setFuture(future);
        }
    );
    m_playTimer->setSingleShot(true);
    connect(m_playTimer, &QTimer::timeout, this, [this] {
        m_playFrameTimer.restart();
        PostProcessingController::next();
    });
    connect(this, &PostProcessingController::lastProcessedImageChanged, this, &PostProcessingController::handleImageChanged);

    connect(this, &PostProcessingController::productModelChanged, this, &PostProcessingController::updateCurrentSeam);
    connect(this, &PostProcessingController::currentSeamChanged, this, &PostProcessingController::currentGraphIdChanged);
    connect(this, &PostProcessingController::currentMeasureTaskChanged, this, &PostProcessingController::updateCurrentSeam);
    connect(this, &PostProcessingController::productChanged, this, &PostProcessingController::updateCurrentSeam);

    connect(this, &PostProcessingController::productChanged, this, &PostProcessingController::hasChangesChanged);
      
}


PostProcessingController::~PostProcessingController() = default;

void PostProcessingController::handleImageChanged()
{
    if (m_lastProcessedImage != m_expectingImage)
    {
        // not the image we are looking for
        return;
    }
    if (!isPlaying())
    {
        if (m_pendingStop)
        {
            m_pendingStop = false;
            performStop();
        }
        return;
    }
    if (!hasNext())
    {
        pause();
    } else
    {
        const auto remaining = frameDuration() - m_playFrameTimer.elapsed();
        if (remaining <= 0)
        {
            m_playTimer->stop();
            next();
        } else
        {
            m_playTimer->start(remaining);
        }
        m_playFrameTimer.restart();
    }
}

bool PostProcessingController::hasNext() const
{
    return m_currentStatus.hasNextFrame();
}

bool PostProcessingController::hasPrevious() const
{
    return m_currentStatus.hasPreviousFrame();
}

template <typename T, typename... Args>
void PostProcessingController::controlFrameSimulation(T method, Args... args)
{ 

    setIsProcessing(true);    
    

    m_simulationStatusWatcher = new QFutureWatcher<SimulationFrameStatus>(this);
    connect(m_simulationStatusWatcher, &QFutureWatcher<SimulationFrameStatus>::finished, this,
        [this]
        {
            m_simulationStatusWatcher->deleteLater();

            m_currentStatus = m_simulationStatusWatcher->result();

            const auto imageIndex = m_pathModel->index(m_currentStatus.frameIndex(), 0);

            m_expectingImage = m_pathModel->data(imageIndex, Qt::UserRole + 2).toInt();
            m_simulationStatusWatcher = nullptr;
            emit imageChanged();

            if (m_lastProcessedImage == m_expectingImage)
            {
                // already received
                handleImageChanged();
            }

            if (!m_playEntireProduct)
            {
                auto imageSeries = m_pathModel->data(imageIndex, Qt::UserRole).toUInt();
                auto imageSeam = m_pathModel->data(imageIndex, Qt::UserRole + 1).toUInt();

                const auto nextImageIndex = m_pathModel->index(m_currentStatus.frameIndex() + 1, 0);
                if (nextImageIndex.isValid())
                {
                    auto nextImageSeries = m_pathModel->data(nextImageIndex, Qt::UserRole).toUInt();
                    auto nextImageSeam = m_pathModel->data(nextImageIndex, Qt::UserRole + 1).toUInt();

                    if (imageSeries != nextImageSeries || imageSeam != nextImageSeam)
                    {
                        pause();
                    }
                }
            }

            setIsProcessing(false);
       }
    );

    auto future = QtConcurrent::run(m_simulationCmdProxy.get(), method, args...);
    m_simulationStatusWatcher->setFuture(future);
}

void PostProcessingController::next()
{
    if (!m_simulationCmdProxy || m_simulationStatusWatcher)
    {
        return;
    }
    controlFrameSimulation(&SimulationCmdProxy::element_type::nextFrame);
}

void PostProcessingController::processAllFrames()
{
    if(!m_pathModel)
    {
        return; 
    }

   setIsProcessing(true);   
    
            
    int rowCount = m_pathModel->rowCount();
    for (int i = 0; i < rowCount; ++i)
    {
      // QModelIndex imageIndex = m_pathModel->index(i, 0);
       jumpToFrame(i);
       m_currentStatus = QtConcurrent::run(m_simulationCmdProxy.get(), &SimulationCmdProxy::element_type::processCurrentImage);      

    }
    
    setIsProcessing(false);
    
}

void PostProcessingController::previous()
{
    if (!m_simulationCmdProxy || m_simulationStatusWatcher)
    {
        return;
    }
    controlFrameSimulation(&SimulationCmdProxy::element_type::previousFrame);
}

void PostProcessingController::jumpToFrame(int index)
{
    if (!m_simulationCmdProxy || m_simulationStatusWatcher)
    {
        return;
    }
    controlFrameSimulation(&SimulationCmdProxy::element_type::jumpToFrame, index);
}

void PostProcessingController::jumpToCurrentFrame()
{
    jumpToFrame(frameIndex());
}

void PostProcessingController::performStop()
{
    if (!m_simulationCmdProxy || m_simulationStatusWatcher)
    {
        return;
    }
    if (m_playEntireProduct)
    {
        controlFrameSimulation(&SimulationCmdProxy::element_type::stop);
    }
    else
    {
        controlFrameSimulation(&SimulationCmdProxy::element_type::seamStart);
    }
}

void PostProcessingController::sameFrame()
{
    if (!m_simulationCmdProxy || m_simulationStatusWatcher)
    {
        return;
    }
    controlFrameSimulation(&SimulationCmdProxy::element_type::sameFrame);
}

void PostProcessingController::play()
{
    if (m_playing)
    {
        return;
    }
    m_playing = true;
    emit isPlayingChanged();
    processAllFrames();
    //.restart();
   // next();
}

void PostProcessingController::pause()
{
    if (!m_playing)
    {
        return;
    }
    m_playing = false;
    m_playTimer->stop();
    emit isPlayingChanged();
}

void PostProcessingController::stop()
{
    pause();

    if (!m_simulationStatusWatcher)
    {
        performStop();
    }
    else
    {
        m_pendingStop = true;
    }
}

bool PostProcessingController::isPlaying() const
{
    return m_playing;
}

bool PostProcessingController::isProcessing() const
{
   return m_isProcessing;
}

bool PostProcessingController::hasPreviousSeam() const
{
    return m_currentStatus.hasPreviousSeam();
}

bool PostProcessingController::hasNextSeam() const
{
    return m_currentStatus.hasNextSeam();
}

void PostProcessingController::nextSeam()
{
    if (!m_simulationCmdProxy || m_simulationStatusWatcher)
    {
        return;
    }
    controlFrameSimulation(&SimulationCmdProxy::element_type::nextSeam);
}

void PostProcessingController::previousSeam()
{
    if (!m_simulationCmdProxy || m_simulationStatusWatcher)
    {
        return;
    }
    controlFrameSimulation(&SimulationCmdProxy::element_type::previousSeam);
}

int PostProcessingController::frameIndex() const
{
    return m_currentStatus.frameIndex();
}

void PostProcessingController::setProductInstance(const QUuid &productId, const QFileInfo &productInstance)
{
    m_dataProduct = productId;
    m_productInstance = productInstance;
    emit productInstanceChanged();
}

precitec::storage::Parameter *PostProcessingController::getFilterParameter(const QUuid &uuid, precitec::storage::Attribute *attribute, const QUuid &filterId, const QVariant &defaultValue)
{
    modifyProduct();
    auto paramSet = currentParameterSet();
    if (!paramSet)
    {
        return nullptr;
    }
    auto it = std::find_if(paramSet->parameters().begin(), paramSet->parameters().end(), [uuid] (auto param) { return param->uuid() == uuid; });
    if (it != paramSet->parameters().end())
    {
        return *it;
    }

    if (attribute)
    {
        auto param = paramSet->createParameter(uuid, attribute, filterId, defaultValue);
        m_storageUpdateProxy->filterParameterCreated(toPoco(m_currentMeasureTask), {param->toFilterParameter()});
        return param;
    }

    return nullptr;
}

namespace
{
Poco::UUID toPoco(const QUuid &uuid)
{
    return Poco::UUID(uuid.toString(QUuid::WithoutBraces).toStdString());
}
}

void PostProcessingController::modifyProduct()
{
    auto product = currentProduct();
    if (std::find(m_modifiedProducts.begin(), m_modifiedProducts.end(), product) != m_modifiedProducts.end())
    {
        return;
    }

    auto copy = storage::Product::fromJson(product->toJson(), this);
    copy->setFilePath(product->filePath());
    copy->setChangeTrackingEnabled(true);
    m_modifiedProducts.push_back(copy);
    emit hasChangesChanged();
}

void PostProcessingController::updateFilterParameter(const QUuid &uuid, const QVariant &value)
{
    modifyProduct();
    auto paramSet = currentParameterSet();
    if (!paramSet)
    {
        return;
    }
    auto it = std::find_if(paramSet->parameters().begin(), paramSet->parameters().end(), [uuid] (auto param) { return param->uuid() == uuid; });
    if (it != paramSet->parameters().end())
    {
        (*it)->setValue(value);
        const auto filterParameter = (*it)->toFilterParameter();
        if (m_storageUpdateProxy)
        {
            m_storageUpdateProxy->filterParameterUpdated(toPoco(m_currentMeasureTask), {filterParameter});
        }
    }
}

precitec::storage::ParameterSet *PostProcessingController::currentParameterSet() const
{
    auto task = currentSeam();
    auto product = currentProduct();
    if (!task || !product)
    {
        return nullptr;
    }
    return product->filterParameterSet(task->graphParamSet());
}

void PostProcessingController::setSubGraphModel(precitec::storage::SubGraphModel *model)
{
    if (m_subGraphModel == model)
    {
        return;
    }
    m_subGraphModel = model;
    disconnect(m_subGraphDestroyedConnection);
    m_subGraphDestroyedConnection = {};
    if (m_subGraphModel)
    {
        m_subGraphDestroyedConnection = connect(model, &QObject::destroyed, this, std::bind(&PostProcessingController::setSubGraphModel, this, nullptr));
    }

    emit subGraphModelChanged();
}

void PostProcessingController::setGraphModel(precitec::storage::GraphModel *graphModel)
{
    if (m_graphModel == graphModel)
    {
        return;
    }
    disconnect(m_graphModelDestroyedConnection);
    m_graphModel = graphModel;
    if (m_graphModel)
    {
        m_graphModelDestroyedConnection = connect(m_graphModel, &QObject::destroyed, this, std::bind(&PostProcessingController::setGraphModel, this, nullptr));
    } else
    {
        m_graphModelDestroyedConnection = {};
    }
    emit graphModelChanged();
}

QUuid PostProcessingController::currentGraphId() const
{
    return getCurrentGraphId(m_currentSeam, m_subGraphModel);
}

storage::Product *PostProcessingController::currentProduct() const
{
    auto it = std::find_if(m_modifiedProducts.begin(), m_modifiedProducts.end(), [this] (auto p) { return p->uuid() == m_product; });
    if (it != m_modifiedProducts.end())
    {
        return *it;
    }
    if (m_productModel)
    {
        return m_productModel->findProduct(m_product);
    }
    return nullptr;
}

void PostProcessingController::setProductModel(precitec::storage::ProductModel *model)
{
    if (m_productModel == model)
    {
        return;
    }
    m_productModel = model;
    disconnect(m_productModelDestroyedConnection);
    disconnect(m_productModelDataChangedConnection);
    if (m_productModel)
    {
        m_productModelDestroyedConnection = connect(m_productModel, &QObject::destroyed, this, std::bind(&PostProcessingController::setProductModel, this, nullptr));
        m_productModelDataChangedConnection = connect(m_productModel, &QAbstractItemModel::dataChanged, this,
            [this] (const QModelIndex &topLeft, const QModelIndex &bottomLeft)
            {
                for (int row = topLeft.row(); row <= bottomLeft.row(); row++)
                {
                    const auto uuid = m_productModel->uuid(m_productModel->index(row, 0));
                    auto it = std::find_if(m_modifiedProducts.begin(), m_modifiedProducts.end(), [uuid] (auto p) { return p->uuid() == uuid; });
                    if (it != m_modifiedProducts.end())
                    {
                        (*it)->deleteLater();
                        m_modifiedProducts.erase(it);
                        emit hasChangesChanged();
                    }
                    if (m_product == uuid)
                    {
                        emit productChanged();
                    }
                }
            }
        );
    } else
    {
        m_productModelDestroyedConnection = {};
        m_productModelDataChangedConnection = {};
    }

    emit productModelChanged();
}

void PostProcessingController::setCurrentMeasureTask(const QUuid &uuid)
{
    if (m_currentMeasureTask == uuid)
    {
        return;
    }
    m_currentMeasureTask = uuid;
    emit currentMeasureTaskChanged();
}

void PostProcessingController::updateCurrentSeam()
{
    auto seam = m_currentSeam;
    if (auto product = currentProduct())
    {
        m_currentSeam = qobject_cast<precitec::storage::Seam*>(product->findMeasureTask(m_currentMeasureTask));

        if (auto interval = qobject_cast<precitec::storage::SeamInterval*>(product->findMeasureTask(m_currentMeasureTask)))
        {
            m_currentSeam = interval->seam();
        }
    } else
    {
        m_currentSeam = nullptr;
    }
    if (seam != m_currentSeam)
    {
        emit currentSeamChanged();
    }
}

void PostProcessingController::saveProductChange()
{
    auto it = std::find_if(m_modifiedProducts.begin(), m_modifiedProducts.end(), [this] (auto p) { return p->uuid() == m_product; });
    if (it == m_modifiedProducts.end())
    {
        return;
    }
    UserLog::instance()->addChange(new ProductModifiedChangeEntry{(*it)->changes()});
    (*it)->save();
}

bool PostProcessingController::hasChanges() const
{
    auto it = std::find_if(m_modifiedProducts.begin(), m_modifiedProducts.end(), [this] (auto p) { return p->uuid() == m_product; });
    return it != m_modifiedProducts.end();
}

void PostProcessingController::discardChanges()
{
    if (m_productModel)
    {
        m_productModel->reloadProduct(m_product);
    }
    if (m_storageUpdateProxy)
    {
        m_storageUpdateProxy->reloadProduct(toPoco(m_product));
    }
}

postprocessing::PostProcessing* PostProcessingController::create(if_ttrigger_cmd_t* p_pTriggerCmdProxy,if_tresults_t*	p_pResultProxy,if_tsystem_status_t* p_pSystemStatusProxy)
{
     return new postprocessing::PostProcessing( p_pTriggerCmdProxy, p_pResultProxy, p_pSystemStatusProxy);
}

fliplib::GraphContainer PostProcessingController::getGraph() const
{
    return getGraphFromModel(m_currentSeam, m_graphModel, m_subGraphModel);
}

std::vector<fliplib::InstanceFilter> PostProcessingController::filterInstances()
{
    return getGraph().instanceFilters;
}

void PostProcessingController::setLastProcessedImage(int number)
{
    if (m_lastProcessedImage == number)
    {
        return;
    }
    m_lastProcessedImage = number;
    emit lastProcessedImageChanged();
}

void PostProcessingController::setFramesPerSecond(int fps)
{
    if (m_framesPerSecond == fps)
    {
        return;
    }
    m_framesPerSecond = fps;
    emit framesPerSecondChanged();
}

void PostProcessingController::setPlayEntireProduct(bool playEntireProduct)
{
    if (m_playEntireProduct == playEntireProduct)
    {
        return;
    }
    m_playEntireProduct = playEntireProduct;
    emit playEntireProductChanged();
}

void PostProcessingController::setIsProcessing(bool isProcessing)
{
    if (m_isProcessing != isProcessing)
    {
        m_isProcessing = isProcessing;
        isProcessingChanged();
    }
}
}//postprocessing
}//components
}//gui
}//precitec
