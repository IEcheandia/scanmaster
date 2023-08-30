#pragma once

#include "abstractModule.h"

#include "message/simulationCmd.proxy.h"
#include "event/storageUpdate.proxy.h"

namespace precitec
{

typedef std::shared_ptr<precitec::interface::TSimulationCmd<precitec::interface::MsgProxy>> SimulationCmdProxy;
typedef std::shared_ptr<precitec::interface::TStorageUpdate<precitec::interface::AbstractInterface>> StorageUpdateProxy;

namespace gui
{

class SimulationModule : public AbstractModule
{
    Q_OBJECT

    Q_PROPERTY(precitec::SimulationCmdProxy simulationCmdProxy READ simulationCmdProxy CONSTANT)

    Q_PROPERTY(precitec::StorageUpdateProxy storageUpdateProxy READ storageUpdateProxy CONSTANT)

public:
    static SimulationModule* instance();

    SimulationCmdProxy simulationCmdProxy() const
    {
        return m_simulationCmdProxy;
    }

    StorageUpdateProxy storageUpdateProxy() const
    {
        return m_storageUpdateProxy;
    }

    Q_INVOKABLE void initialize();

private:
    explicit SimulationModule();

    void init() override;
    void registerPublications() override;

    SimulationCmdProxy m_simulationCmdProxy;
    std::shared_ptr<precitec::interface::TStorageUpdate<precitec::interface::EventProxy>> m_storageUpdateProxy;
};

}
}

