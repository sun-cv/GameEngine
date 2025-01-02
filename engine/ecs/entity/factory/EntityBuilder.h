#pragma once

#include "CoreUtility.h"

#include "ECSDefinition.h"

#include "EntityManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"

#include "Entity.h"


namespace ECS
{

class EntityBuilder
{
    private:
        std::shared_ptr<EntityManager>      entityManager;
        std::shared_ptr<MeshManager>        meshManager;
        std::shared_ptr<MaterialManager>    materialManager;
        std::optional<Entity>               entity;

    public:
         EntityBuilder(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<MeshManager> meshManager, std::shared_ptr<MaterialManager> materialManager);
        ~EntityBuilder();

        EntityBuilder& create(std::string tag);
        EntityBuilder& enemy(bool value);
        EntityBuilder& player(bool value);
        EntityBuilder& lifespan(size value);
        EntityBuilder& position(Vector2 vector);
        EntityBuilder& render(std::string mesh, std::string material);
        EntityBuilder& title(std::string name);
        EntityBuilder& velocity(Vector2 vector);
        Entity complete();
};
}