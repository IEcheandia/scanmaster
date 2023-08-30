#include "simulationModule.h"
#include "productModel.h"

#include <QtConcurrentRun>

namespace precitec
{
namespace gui
{

SimulationModule::SimulationModule()
    : AbstractModule("SIMULATION")
    , m_simulationCmdProxy(std::make_shared<TSimulationCmd<MsgProxy>>())
    , m_storageUpdateProxy(std::make_shared<TStorageUpdate<EventProxy>>())
{
    productModel()->setCleanupEnabled(false);
}

SimulationModule* SimulationModule::instance()
{
    static SimulationModule simulationModule;
    return &simulationModule;
}

void SimulationModule::init()
{
    AbstractModule::init();
}

void SimulationModule::initialize()
{
    QtConcurrent::run(this, &SimulationModule::init);
}

void SimulationModule::registerPublications()
{
    AbstractModule::registerPublications();

    registerPublication(m_simulationCmdProxy.get());
    registerPublication(m_storageUpdateProxy.get());
}

}
}

