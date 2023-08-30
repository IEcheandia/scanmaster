#include "Mod_Analyzer.h"
//#include "analyzer/stdGraphBuilder.h"
#include "analyzer/product.h"
#include "analyzer/resultHandler.h"
#include "analyzer/centralDeviceManager.h"
//#include "analyzer/hwParameters.h"
#include "analyzer/inspectTimer.h"
//#include "analyzer/referenceCurves.h"
#include "analyzer/graphAssistent.h"
#include "analyzer/deviceParameter.h"
#include "analyzer/processingThread.h"
#include "analyzer/inspectManager.h"

//#include "math/calibration3DCoords.h" 
//#include "math/calibrationData.h"
// wm includes

#include "geo/array.h"
#include "geo/range.h"

#include "filter/productData.h"
#include "postProcessing.h"
#include "common/measureTask.h"
#include "common/product.h"
#include "common/frame.h"
#include "common/seamData.h"
#include "common/product1dParameter.h"
//#include "common/productCurves.h"
#include "common/defines.h"

#include "message/db.interface.h"
//#include "message/weldHead.interface.h"

#include "event/sensor.h"
#include "event/triggerCmd.interface.h"
#include "event/results.interface.h"
//#include "event/recorder.interface.h"
//#include "event/recorderPoll.interface.h"
//#include "event/systemStatus.interface.h"
//#include "event/videoRecorder.interface.h"

#include "fliplib/SynchronePipe.h"
#include "fliplib/NullSourceFilter.h"

#include "Poco/UUID.h"
#include "Poco/Thread.h"
#include <filter/sensorFilterInterface.h>
#include <analyzer/signalAdapter.h>

namespace precitec
{
namespace gui
{
namespace components
{
namespace postprocessing 
{
using namespace analyzer;
class ImageSender;

PostProcessing::PostProcessing(
				if_ttrigger_cmd_t*		p_pTriggerCmdProxy,
				if_tresults_t*			p_pResultProxy,
				if_tsystem_status_t*	p_pSystemStatusProxy)
:	//m_pDbProxy						{ p_pDbProxy },
	m_pTriggerCmdProxy				{ p_pTriggerCmdProxy },
	m_pResultProxy					{ p_pResultProxy },	
	m_pSystemStatusProxy			{ p_pSystemStatusProxy },
    m_oPipeImageFrame				{ &m_oNullSourceFilters[0], SensorFilterInterface::SENSOR_IMAGE_FRAME_PIPE },
    m_oResultHandler				{ m_pResultProxy }
{};

	


void PostProcessing::startProcessing(size_t oIdxWorkerCur)
{
    std::weak_ptr<precitec::analyzer::ImageSender> imageSenderPtr = m_imageSender;
	std::unique_ptr<analyzer::SignalAdapter> signalAdapter{ new analyzer::SignalAdapter{ oIdxWorkerCur, &m_oInspectTimer, &m_oPipeImageFrame, m_oPipesSampleFrame[oIdxWorkerCur].get(), m_pActiveGraph }};
	signalAdapter->setResultHandler(&m_oResultHandler);
    auto &triggerContext = m_oTriggerContexts[oIdxWorkerCur];
	signalAdapter->setImageNumber(triggerContext.imageNumber());
    signalAdapter->setImage(m_oImageFrames[oIdxWorkerCur]);
    signalAdapter->setSamples(m_oSampleFrames[oIdxWorkerCur]);
    auto processingMode = m_oProcessingModes[oIdxWorkerCur];
    signalAdapter->setProcessingMode(processingMode);
    signalAdapter->setImageSensorId(m_oImageIds[oIdxWorkerCur]);
    signalAdapter->setOverlayCanvas(&m_oCanvasBuffer[oIdxWorkerCur]);
    signalAdapter->setImageSender(imageSenderPtr);
    signalAdapter->setHardwareCamera(m_hasHardwareCamera);
    triggerContext.setSeamSeriesNumber(m_pActiveSeamSeries->m_oNumber);
    triggerContext.setSeamNumber(m_pActiveSeam->m_oNumber);
    signalAdapter->setTriggerContext(triggerContext);
    signalAdapter->setLastProcessedImage(m_lastProcessedImage);
   
    if (m_oWorkers[oIdxWorkerCur].scheduleWork(std::move(signalAdapter), std::chrono::microseconds(int(m_pActiveSeamInterval->m_pMeasureTask->getTimeDelta() * 1000))))
    {
        m_lastProcessedImage = triggerContext.imageNumber();
        ++m_oNbSeamSignaled;
    }
    else
    {
        wmLog(eError, "Failed to pass SignalAdapter for %d to ProcessingThread as the ProcessingThread is still processing previous SignalAdapter.\n", triggerContext.imageNumber());
        processingMode = ProcessingMode::Overtriggered;
        if (m_lastSkippedImageNumber < triggerContext.imageNumber())
        {
            // already set by ::data
            m_oNumImagesSkippedInInspection++;
            m_lastSkippedImageNumber = triggerContext.imageNumber();
        }
    }

    double value = 0.0;
    switch (processingMode)
    {
    case ProcessingMode::Overtriggered:
        value = 1.0;
        break;
    case ProcessingMode::MissingImage:
        value = 2.0;
        break;
    case ProcessingMode::OutOfOrderImage:
        value = 3.0;
        break;
    case ProcessingMode::Normal:
    default:
        break;
    }
    // send ProcessingMode as result
    const auto oImageContext = makeImageContext( triggerContext );
    ResultDoubleArray oProcessingModeResult (
            Poco::UUID::null(),
            InspectManagerImageProcessingMode,
            ResultType::AnalysisOK,
            oImageContext,
            GeoDoublearray{oImageContext, precitec::geo2d::Doublearray{1, value}, ResultType::AnalysisOK},
            precitec::geo2d::Range1d(),
            false);
    // pass to sum error handling
    m_oResultHandler.sendResult( oProcessingModeResult );
    // and send to result proxy
    m_pResultProxy->result( oProcessingModeResult );

}

}
}
}
}
