#pragma once

#include "CoreUtility.h"
#include "Entity.h"

#include "MeshManager.h"
#include "MaterialManager.h"


namespace ECS
{
class EntityManager 
{
    private:
        std::vector<Entity>                     entities;
        std::vector<Entity>                     createQueue;
        std::vector<Entity>                     destroyQueue;

        std::shared_ptr<MeshManager>            meshManager;
        std::shared_ptr<MaterialManager>        materialManager;

    private:
        void createEntities ();
        void destroyEntities();

    public:
        EntityManager();                         
       ~EntityManager();

        void   update();

        Entity createEntity         (const std::string& tag);
        void destroyEntity          (Entity entity);

        std::vector<Entity> getEntities();
};
}

#define CreateEntity(tag) ECS::EntityManager::createEntity(tag);