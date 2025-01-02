#include "EntityManager.h"

#include "EntityMemoryPool.h"

namespace ECS
{
EntityManager::EntityManager()
{
    Log_(Log::System, Log::mEntity, "Initializing..");

    MemoryPool_();

    Log_(Log::System, Log::mEntity, "Initialized successfully!");
}


EntityManager::~EntityManager()
{
}


Entity EntityManager::createEntity(const std::string& tag)
{
    Entity entity(AllocateEntity_(tag));

    if (!entity.isValid())
    {
        Log_(Log::Warning, Log::mEntity, "INVALID_ENTITY detected" );
        destroyQueue.push_back(entity);
        return entity;
    }
    createQueue.push_back(entity);
    return entity;
}

void EntityManager::destroyEntity(Entity entity)
{
    Log_(Log::Debug, Log::mEntity, "Destroying entity {} ", entity.getID());
    destroyQueue.push_back(entity);
}


void EntityManager::update()
{   
    createEntities();
    destroyEntities();
}



void EntityManager::createEntities()
{
    if (createQueue.size() == 0)
    {
        return;
    }

    int created = 0;
    for (auto entity : createQueue)
    {
        entities.push_back(entity);
        created++;
    }
    Log_(Log::Debug, Log::mEntity, "Created {} Entities", created);
    createQueue.clear();
}


void EntityManager::destroyEntities()
{
    if (destroyQueue.size() == 0)
    {
        return;
    }

    for (auto entity : destroyQueue)
    {
        auto iterator = std::find(entities.begin(), entities.end(), entity);
        if (iterator == entities.end())
        {
            Log_(Log::Warning, Log::mEntity, "Entity ID {} not found for destruction", entity.getID());
            return;
        }
        entities.erase(iterator);
        Log_(Log::Trace, Log::mEntity, "Destroyed entities location {}", std::distance(entities.begin(), iterator) );
    }
    destroyQueue.clear();
    Log_(Log::Debug, Log::mEntity, "Cleared destroy Queue");
}

std::vector<Entity> EntityManager::getEntities()
{
    return entities;
}
}