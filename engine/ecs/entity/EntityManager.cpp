#include "EntityManager.h"


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}


Entity EntityManager::addEntity(const std::string& tag)
{
    Entity entity(AllocateEntity_(tag));

    if (!entity.isValid())
    {
        Log_(Log::Error, Log::EntityManager, "INVALID_ENTITY detected" )
        destroyQueue.push_back(entity);
        return entity;
    }
    createQueue.push_back(entity);
    return entity;
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

    for (auto entity : createQueue)
    {
        entities.push_back(entity);
    }
    Log_(Log::Debug, Log::EntityManager, "Cleared create Queue");
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
        auto iterator = std::find(destroyQueue.begin(), destroyQueue.end(), entity);
        if (iterator == destroyQueue.end())
        {
            Log_(Log::Error, Log::EntityManager, "Entity ID {} not found for destruction", entity.getID());
            return;
        }

        entities.erase(iterator);
    }
    Log_(Log::Debug, Log::EntityManager, "Cleared destroy Queue");
    destroyQueue.clear();
}