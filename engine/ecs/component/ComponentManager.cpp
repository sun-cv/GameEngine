#include "ComponentManager.h"



ECS::ComponentManager::ComponentManager(std::shared_ptr<EntityMemoryPool> entityMemoryPool) : entityMemoryPool(entityMemoryPool)
{
    LogSuccess(Log::mComponent);
}

ECS::ComponentManager::~ComponentManager()
{
    LogPowerDown(Log::mComponent);
}
