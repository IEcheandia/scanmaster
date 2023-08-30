#include <QQmlExtensionPlugin>
#include <QtQml/QtQml>
#include "postProcessing.h"
#include "postProcessingController.h"


class PostProcessingPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);
};

void PostProcessingPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(qstrcmp(uri, "precitec.gui.components.postprocessingcontroller") == 0);
    qmlRegisterType<precitec::gui::components::postprocessing::PostProcessingController >(uri, 1, 0, "PostProcessingController");
    
}

#include "main.moc"

