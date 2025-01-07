#include "EntityMemoryPool.h"

namespace ECS
{

EntityMemoryPool::EntityMemoryPool()
{
    LogStartup(Log::EMP);
    try
    {
        initializeMemoryPool();
    }
    catch(Exceptions)
    {
        LogFailure(Log::EMP, error)
    }
    LogSuccess(Log::EMP);
}

EntityMemoryPool::~EntityMemoryPool()
{
    LogPowerDown(Log::EMP)
}   


    // throw
void EntityMemoryPool::initializeMemoryPool()
{   
    initializeVector<bool>                      (active);
    initializeVector<bool>                      (dirty);

    initializeComponents<0, ComponentCount>     (componentPool);
}


    // throw
Entity EntityMemoryPool::allocateEntity()
{   

    Entity availableID = allocateEntityID();

    initializeEntity(availableID);
        
    return availableID;

}


void EntityMemoryPool::deallocateEntity(Entity entityID)
{
    active[entityID] = false;
}


Entity EntityMemoryPool::allocateEntityID()
{
    auto iterator = std::find(active.begin(), active.end(), false);
    if (iterator == active.end())
    {
        Throw(Error::runtime, "No available entity allocation INVALID_ENTITY")
    }
    return std::distance(active.begin(), iterator);
}


    //throw
void EntityMemoryPool::initializeEntity(Entity entityID)
{
    resetComponent<Enemy>       (entityID);
    resetComponent<Lifespan>    (entityID);
    resetComponent<Player>      (entityID);
    resetComponent<Position>    (entityID);
    resetComponent<Render>      (entityID);
    resetComponent<Title>       (entityID);
    resetComponent<Transform>   (entityID);
    resetComponent<Velocity>    (entityID);

    active[entityID] = true;
    dirty [entityID] = true;

    Log(Log::Debug, Log::EMP, "Instantiated entity with id {}", entityID);
}

void EntityMemoryPool::tagEntity(Entity entityID, std::string tag)
{
    entityTags[tag].push_back(entityID);
}


const std::vector<Entity>& EntityMemoryPool::getTag(std::string tag)
{
    return entityTags[tag];
}


const std::vector<Entity> EntityMemoryPool::getActive()
{
    return filter(dirty);
}


const std::vector<Entity> EntityMemoryPool::getDirty()
{
    return filter(dirty);
}

std::vector<Entity> EntityMemoryPool::filter(std::vector<bool> vector)
{
    std::vector<Entity> buffer;

    for (size_t entity = 0; entity < vector.size(); entity++)
    {
        if (vector[entity])
        {
            buffer.push_back(entity);
        }
    }
    return buffer;
}




}