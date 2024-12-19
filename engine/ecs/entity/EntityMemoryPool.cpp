#include "EntityMemoryPool.h"
#include "Entity.h"


EntityMemoryPool::EntityMemoryPool()
{
    Log_(Log::System, Log::EMP, "Initializing..");

    initializeComponents<0, ECS::ComponentCount>(pool);
    initializeVector<bool>                      (active);
    initializeVector<std::string>               (tags);

    Log_(Log::System, Log::EMP, "Initialized successfully!");
}   


ECS::Type EntityMemoryPool::getNextEntityIndex()
{
    auto iterator = std::find(active.begin(), active.end(), false);
    if (iterator == active.end())
    {
        Log_(Log::Error, Log::EMP, "No available entity allocation returning INVALID_ENTITY");
        return ECS::INVALID_ENTITY;
    }

    return std::distance(active.begin(), iterator);
}


ECS::Type EntityMemoryPool::allocateEntity(const std::string& tag)
{   
    ECS::Type availableID= getNextEntityIndex();
    if (availableID == ECS::INVALID_ENTITY)
    {
        return ECS::INVALID_ENTITY;
    }

    initializeEntity(availableID, tag);
    return availableID;
}


void EntityMemoryPool::initializeEntity(ECS::Type entityID, const std::string& tag)
{
    resetComponent<Enemy>   (pool, entityID);
    resetComponent<Lifespan>(pool, entityID);
    resetComponent<Player>  (pool, entityID);
    resetComponent<Position>(pool, entityID);
    resetComponent<Render>  (pool, entityID);
    resetComponent<Velocity>(pool, entityID);

    active[entityID] = true;
    tags[entityID] = tag;

    Log_(Log::Debug, Log::EMP, "Instantiated entity with id {}", entityID);
}