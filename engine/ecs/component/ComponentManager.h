#pragma once

#include "CoreUtility.h"
#include "ECSValue.h"

#include "EntityMemoryPool.h"


namespace ECS
{
class ComponentManager
{   // Variables
    private:
            // Memory allocation
        std::shared_ptr<EntityMemoryPool>       entityMemoryPool;

    public: // NA

    // External templates
    public:
            // Add
        template <typename component>
        component& add(Entity entityID)
        {
            auto&  vComponent = entityMemoryPool->addComponent<component>(entityID);
            return vComponent;
        }
            // Edit
        template <typename component>
        component& edit(Entity entityID)
        {
            auto&  vComponent = entityMemoryPool->editComponent<component>(entityID);
            return vComponent;
        }
            // Get - const
        template <typename component>
        const component& get(Entity entityID)
        {
            auto&  vComponent = entityMemoryPool->getComponent<component>(entityID);
            return vComponent;
        }
            // Has - bool
        template <typename component>
        bool has(Entity entityID)
        {
            return entityMemoryPool->hasComponent<component>(entityID);
        }
            // Remove
        template <typename component>
        component& remove(Entity entityID)
        {
            entityMemoryPool->removeComponent<component>(entityID);
        }


    // Internal templates
    private:
    public:


    public:
        ComponentManager(std::shared_ptr<EntityMemoryPool> entityMemoryPool);
       ~ComponentManager();

};
}