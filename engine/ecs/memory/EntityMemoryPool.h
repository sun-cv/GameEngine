#pragma once

#include "CoreUtility.h"

#include "ECSValue.h"
#include "ECSDefinition.h"

namespace ECS
{
class EntityMemoryPool
{   // Variables
    private:
            // Entity Management
        std::vector<bool>                       active;
        std::vector<bool>                       dirty;

            // Component Management    
        std::tuple<
            std::vector<Enemy>,
            std::vector<Lifespan>,
            std::vector<Player>,
            std::vector<Position>,
            std::vector<Render>,
            std::vector<Title>,
            std::vector<Transform>,
            std::vector<Velocity>
        >                                       componentPool;

            // Filtering Management
        std::unordered_map<
            std::string,
            std::vector<Entity>
        >                                       entityTags;

    public: // NA

    // Functions
    private:    
        void    initializeMemoryPool();

            // Helper
        void    initializeEntity    (Entity entityID);
        Entity  allocateEntityID    ();
    public:
        Entity  allocateEntity      ();
        void    deallocateEntity    (Entity entityID);
            // Filter
        std::vector<Entity> filter  (std::vector<bool> vector);
        void tagEntity              (Entity entityID, std::string tag);
            // Getter
        const std::vector<Entity>&  getTag (std::string tag);
        const std::vector<Entity>  getActive();
        const std::vector<Entity>  getDirty();
    // External Templates
    public: // Entity Functions
            // Add
        template <typename component>
        component& addComponent(Entity entityID)
        {
            auto&  components = std::get<std::vector<component>>(componentPool);
            auto&  component  = components[entityID];
            component.active  = true;
            dirty[entityID]   = true;

            return component;
        };
            // Edit
        template <typename component>
        component& editComponent(Entity entityID)
        {
            auto&  components = std::get<std::vector<component>>(componentPool);
            auto&  component  = components[entityID];
            dirty[entityID]   = true;

            return component;
        };
            // Get
        template <typename component>
        const component& getComponent(Entity entityID)
        {
            auto&  components = std::get<std::vector<component>>(componentPool);
            auto&  component  = components[entityID];

            return component;
        };
            // Has
        template <typename component>
        bool hasComponent(Entity entityID)
        {
            auto&  components = std::get<std::vector<component>>(componentPool);
            auto&  component  = components[entityID];

            return component.active;
        };
            // Remove
        template <typename component>
        void removeComponent(Entity entityID)
        {
            auto& components = std::get<std::vector<component>>(componentPool);
            auto& component  = components[entityID];
            component.active = false;
            dirty[entityID]  = true;
        };

    // Internal Templates
    private:
            // Component tuple vector initialization templates
        template<size_t index = 0, size_t count>
        typename std::enable_if<index == count, void>::type
        initializeComponents(ComponentTuple&)
        {
        };

        template<size_t index = 0, size_t count>
        typename std::enable_if<index < count, void>::type
        initializeComponents(ComponentTuple& componentPool)
        {
            initializeVector(std::get<index>(componentPool));
            initializeComponents<index + 1, count>(componentPool);
        };

        template<typename component>
        void initializeVector(std::vector<component>& vector)
        {
            vector.resize(MAX_ENTITIES);
            Log(Log::Trace, Log::EMP, "Instantiated vector with size {}", vector.size());
        };
            // Reset Helper
        template <typename component>
        void resetComponent(Entity entityID)
        {
            auto& components = std::get<std::vector<component>>(componentPool);
            components[entityID] = component();
            Log(Log::Trace, Log::EMP, "Reset component active {} of {}", entityID, typeid(component).name());
        };

        public:
            EntityMemoryPool();
           ~EntityMemoryPool();
};
}

