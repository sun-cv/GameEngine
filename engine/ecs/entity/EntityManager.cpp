#include "EntityManager.h"

#include "EntityMemoryPool.h"

namespace ECS
{
EntityManager::EntityManager(std::shared_ptr<EntityMemoryPool> entityMemoryPool) : entityMemoryPool(entityMemoryPool)
{
    LogSuccess(Log::mEntity);
}


EntityManager::~EntityManager()
{
    LogPowerDown(Log::mEntity);
}

    // Returns INVALID_ENTITY if creation fails
Entity EntityManager::createEntity()
{
    try
    {
        Entity entityID = entityMemoryPool->allocateEntity();
        return entityID;
    }
    catch(Exceptions)
    {
        Log(Log::Error, Log::mEntity, "INVALID_ENTITY created : {}", error.what());
        return INVALID_ENTITY;
    }
}


void EntityManager::destroy(Entity entityID)
{
    entityMemoryPool->deallocateEntity(entityID);
}


bool EntityManager::validate(Entity entityID)
{
    return entityID == INVALID_ENTITY;
}


void EntityManager::tag(Entity entityID, std::string tag)
{
    entityMemoryPool->tagEntity(entityID, tag);
}


const std::vector<Entity> EntityManager::getEntities()
{
    return entityMemoryPool->getActive();
}


const std::vector<Entity> EntityManager::getDirtyEntities()
{
    return entityMemoryPool->getDirty();
}

}