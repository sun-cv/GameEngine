#pragma once

#include "CoreUtility.h"

#include "EntityManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"

namespace ECS {
    
class EntityFactory
{
    private:
        std::shared_ptr<EntityManager>      entityManager;
        std::shared_ptr<MeshManager>        meshManager;
        std::shared_ptr<MaterialManager>    materialManager;
    public:
         EntityFactory(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<MeshManager> meshManager, std::shared_ptr<MaterialManager> materialManager);
        ~EntityFactory();

        // Entity& createEntity(std::string tag);


};
}