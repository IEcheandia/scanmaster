import QtQuick 2.5
import QtQuick.Layouts 1.3
import precitec.gui.components.application 1.0

import Precitec.AppGui 1.0
import precitec.gui 1.0
import precitec.gui.general 1.0

SideTabView {
    id: wizardPage
    property var graphModel: null
    property var subGraphModel: null
    property var attributeModel: null
    property var keyValueAttributeModel: null
    property var resultsConfigModel: null
    property var errorConfigModel: null
    property var sensorConfigModel: null
    property var qualityNormModel: null
    property var pdfFile: OnlineHelp.HasNoPdf
    property var loggerModel: null
    property var onlineHelp: null
    property var productController: null
    property bool scanTrackerVisible: false
    property var screenshotTool: null

    signal updateSettings()
    signal plotterSettingsUpdated()
    signal wizardPageEnabledChanged(bool enabled)

    function configureSeam(productId, seamSeriesId, seamId)
    {
        wizardPage.currentIndex = wizardFilterModel.mapFromSource(rootWizardModel.indexForComponent(WizardModel.ProductStructure)).row;
        productStructureLoader.item.configureSeam(productId, seamSeriesId, seamId);
    }

    function configureSeamSeries(productId, seamSeriesId)
    {
        wizardPage.currentIndex = wizardFilterModel.mapFromSource(rootWizardModel.indexForComponent(WizardModel.ProductStructure)).row;
        productStructureLoader.item.configureSeamSeries(productId, seamSeriesId);
    }

    WizardModel {
        id: rootWizardModel
    }

    WizardFilterModel {
        id: wizardFilterModel
        sourceModel: rootWizardModel
        yAxisAvailable: yAxisInformation.axisEnabled
        ledCalibration: GuiConfiguration.ledCalibration
        sensorGrabberAvailable: HardwareModule.sensorGrabberEnabled
        idmAvailable: HardwareModule.idmEnabled
        scanTracker: HardwareModule.scanTrackerEnabled
        coaxCameraAvailable: HardwareModule.coaxCameraEnabled
        scheimpflugCameraAvailable: HardwareModule.scheimpflugCameraEnabled
        ledCameraAvailable: HardwareModule.ledCameraEnabled
        lineLaser1Available: HardwareModule.lineLaser1Enabled
        lineLaser2Available: HardwareModule.lineLaser2Enabled
        lineLaser3Available: HardwareModule.lineLaser3Enabled
        ledAvailable: HardwareModule.ledEnabled
        laserControlAvailable: HardwareModule.laserControlEnabled
        zCollimator: HardwareModule.zCollimatorEnabled
        lwmAvailable: HardwareModule.lwmEnabled
        newsonScannerAvailable: HardwareModule.newsonScannerEnabled
        scanlabScannerAvailable: HardwareModule.scanlabScannerEnabled
        cameraInterfaceType: HardwareModule.cameraInterfaceType
        scanTracker2DAvailable: HardwareModule.scannerGeneralMode == HardwareModule.ScanTracker2DMode
        showProductionSetup : GuiConfiguration.formatHardDisk
        externalLwmAvailable: SystemConfiguration.Communication_To_LWM_Device_Enable
    }

    model: wizardFilterModel

    Component {
        id: hardwareRoiComponent
        HardwareRoi {
            id: hardwareRoi
            screenshotTool: wizardPage.screenshotTool
        }
    }

    Component {
        id: hardwareRoiGigEComponent
        HardwareRoiGigE {
            id: hardwareRoiGigE
            screenshotTool: wizardPage.screenshotTool
            keyValueAttributeModel: wizardPage.keyValueAttributeModel
        }
    }

    contentItem: StackLayout {
        anchors.fill: parent
        currentIndex: wizardFilterModel.mapToSource(wizardFilterModel.index(wizardPage.currentIndex, 0)).row

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: HardwareAxis {
                id: hardwareAxis
                screenshotTool: wizardPage.screenshotTool
            }
            Component.onCompleted: {
                if (visible) {
                    active = true;
                }
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: HardwareModule.cameraInterfaceType == 0 ? hardwareRoiComponent : (HardwareModule.cameraInterfaceType == 1 ? hardwareRoiGigEComponent : undefined)
            Component.onCompleted: {
                if (visible) {
                    active = true;
                }
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: IDMSetup {
                id: idmSetup
            }
            Component.onCompleted: {
                if (visible) {
                    active = true;
                }
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: LWM {
                id: lwmPage
                sensorConfigModel: wizardPage.sensorConfigModel
                attributeModel: wizardPage.keyValueAttributeModel

                onPlotterSettingsUpdated: wizardPage.plotterSettingsUpdated()

                Connections {
                    target: wizardPage
                    function onUpdateSettings() {
                        productStructure.updateSettings()
                    }
                }
            }
            Component.onCompleted: {
                if (visible) {
                    active = true;
                }
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: ScanLabScanner {
                id: scanLabScanner
                attributeModel: wizardPage.keyValueAttributeModel
                screenshotTool: wizardPage.screenshotTool
                figureSimulationVisible: !wizardFilterModel.scanTracker2DAvailable
            }
            Component.onCompleted: {
                if (visible) {
                    active = true;
                }
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: ToolCenterPointOCT {
                id: toolCenterPointOCT
                screenshotTool: wizardPage.screenshotTool
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: IDMCalibration {
                id: idmCalibration
                screenshotTool: wizardPage.screenshotTool
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: ScanfieldCalibration {
                id: scanfieldCalibration
                screenshotTool: wizardPage.screenshotTool
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: CameraCalibration {
                id: cameraCalibration
                screenshotTool: wizardPage.screenshotTool
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: CameraChessboardCalibration {
                id: cameraChessboardCalibration
                screenshotTool: wizardPage.screenshotTool
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: LEDCalibration {
                id: ledCalibration
                screenshotTool: wizardPage.screenshotTool
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: FocusPosition {
                id: focusPosition
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: ToolCenterPoint {
                id: toolCenterPoint
                screenshotTool: wizardPage.screenshotTool
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    productStructureLoader.active = true;
                    active = true;
                }
            }
            sourceComponent: LaserControl {
                id: laserControl
                attributeModel: wizardPage.keyValueAttributeModel
                productController: wizardPage.productController
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    productStructureLoader.active = true;
                    active = true;
                }
            }
            sourceComponent: LaserControlDelay {
                id: laserControlDelay
            }
        }

        Loader {
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: ScanTracker {
                id: scanTracker
                logModel: wizardPage.loggerModel
                screenshotTool: wizardPage.screenshotTool
                Component.onCompleted: {
                    wizardPage.scanTrackerVisible = Qt.binding(function() { return scanTracker.visible; });
                }
            }
        }

        Loader {
            id: figureEditorLoader
            active: false
            onVisibleChanged:
            {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: FigureEditor {
                id: figureEditor
                screenshot: wizardPage.screenshotTool
            }
        }

        Loader {
            id: productStructureLoader
            active: false
            onVisibleChanged: {
                if (visible)
                {
                    active = true;
                }
            }
            sourceComponent: ProductStructure {
                id: productStructure
                wizardModel: rootWizardModel
                graphModel: wizardPage.graphModel
                subGraphModel: wizardPage.subGraphModel
                attributeModel: wizardPage.attributeModel
                keyValueAttributeModel: wizardPage.keyValueAttributeModel
                resultsConfigModel: wizardPage.resultsConfigModel
                errorConfigModel: wizardPage.errorConfigModel
                sensorConfigModel: wizardPage.sensorConfigModel
                qualityNormModel: wizardPage.qualityNormModel
                onlineHelp: wizardPage.onlineHelp
                onPlotterSettingsUpdated: wizardPage.plotterSettingsUpdated()
                screenshotTool: wizardPage.screenshotTool
                onProductStructureEnabledChanged: {
                    wizardPage.enabled = enabled;
                    wizardPage.wizardPageEnabledChanged(enabled);
                }
                Connections {
                    target: wizardPage
                    function onUpdateSettings() {
                        productStructure.updateSettings()
                    }
                }
                Component.onCompleted: {
                    wizardPage.productController = productStructure.productController;
                }
            }
        }
    }
}
