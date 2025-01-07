#pragma once

#include "CoreUtility.h"

#include "ECSDefinition.h"
#include "ECSValue.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"

// REWORK REQUIRED

namespace ECS
{

class EntityBuilder
{   // Variables
    private: // Dependencies
        std::shared_ptr<EntityManager>      entityManager;
        std::shared_ptr<ComponentManager>   componentManager;

        Entity                              entity = INVALID_ENTITY;
    // Functions
    public: // Builder
        EntityBuilder& create();
        EntityBuilder& enemy(bool value);
        EntityBuilder& player(bool value);
        EntityBuilder& lifespan(size value);
        EntityBuilder& position(Vector2 vector);
        EntityBuilder& render(std::string mesh, std::string material, unsigned int layer);
        EntityBuilder& title(std::string name);
        EntityBuilder& transform();
        EntityBuilder& velocity(Vector2 vector);

            // Finalize build
        Entity complete();

    public:
        EntityBuilder(std::shared_ptr<EntityManager> entityManager, std::shared_ptr<ComponentManager> componentManager);
       ~EntityBuilder();
};
}