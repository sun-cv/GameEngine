#include "EntityMemoryPool.h"

namespace ECS
{
EntityMemoryPool::EntityMemoryPool()
{
    Log_(Log::System, Log::EMP, "Initializing..");

    initializeComponents<0, ComponentCount>     (pool);
    initializeVector<bool>                      (active);
    initializeVector<bool>                      (dirty);
    // initializeVector<std::string>               (tags);

    Log_(Log::System, Log::EMP, "Initialized successfully!");
}   


size_t EntityMemoryPool::getNextEntityIndex()
{
    auto iterator = std::find(active.begin(), active.end(), false);
    if (iterator == active.end())
    {
        Log_(Log::Error, Log::EMP, "No available entity allocation returning INVALID_ENTITY");
        return INVALID_ENTITY;
    }
    return std::distance(active.begin(), iterator);
}


EntityMemoryPool & EntityMemoryPool::getInstance()
{

    static EntityMemoryPool instance;
    return instance;

}

size_t EntityMemoryPool::allocateEntity(const std::string& tag)
{   
    size_t availableID = getNextEntityIndex();
    if (availableID == INVALID_ENTITY)
    {
        return INVALID_ENTITY;
    }

    initializeEntity(availableID, tag);
    return availableID;
}

void EntityMemoryPool::deallocateEntity(size_t entityID)
{
    active[entityID] = false;
}

void EntityMemoryPool::initializeEntity(size_t entityID, const std::string& tag)
{
    resetComponent<Enemy>       (pool, entityID);
    resetComponent<Lifespan>    (pool, entityID);
    resetComponent<Player>      (pool, entityID);
    resetComponent<Position>    (pool, entityID);
    resetComponent<Render>      (pool, entityID);
    resetComponent<Title>       (pool, entityID);
    resetComponent<Transform>   (pool, entityID);
    resetComponent<Velocity>    (pool, entityID);

    active[entityID] = true;
    dirty[entityID] = true;
    // tags[tag] = entityID;

    Log_(Log::Debug, Log::EMP, "Instantiated entity with id {}", entityID);
}
}