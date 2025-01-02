#pragma once

#include "CoreUtility.h"

#include "ECSValue.h"
#include "ECSDefinition.h"

namespace ECS
{
class EntityMemoryPool
{
    private:
        EntityMemoryPool();

        VectorTuple pool;
        
        size_t                                  totalEntities;
        std::vector<std::string>                tags;    
        std::vector<bool>                       active;

        void initializeEntity       (size_t entityID, const std::string& tag);
        size_t getNextEntityIndex   ();
        
    public: 
        EntityMemoryPool            (const EntityMemoryPool &) = delete;
        EntityMemoryPool &operator= (const EntityMemoryPool &) = delete;

        static EntityMemoryPool& getInstance();

        size_t allocateEntity       (const std::string& tag);
        void deallocateEntity       (size_t entityID);

    private:

        template<typename component>
        void initializeVector(std::vector<component>& vector)
        {
            vector.resize(MAX_ENTITIES);
            Log_(Log::Trace, Log::EMP, "Instantiated entity limit {} vector of {}", vector.size(), typeid(component).name());
        };

        template<size_t index = 0, size_t count>
        typename std::enable_if<index == count, void>::type
        initializeComponents(VectorTuple&)
        {
        };

        template<size_t index = 0, size_t count>
        typename std::enable_if<index < count, void>::type
        initializeComponents(VectorTuple& tuple)
        {
            initializeVector(std::get<index>(tuple));
            initializeComponents<index + 1, count>(tuple);
        };

        template <typename component>
        void resetComponent(VectorTuple& tuple, size_t entityID)
        {
            auto& components = std::get<std::vector<component>>(tuple);
            components[entityID] = component();
            Log_(Log::Trace, Log::EMP, "Reset component exists {} of {}", components[entityID].exists, typeid(component).name());
        };

    public:

        template <typename component>
        component& addComponent(size_t entityID)
        {
            auto& components = std::get<std::vector<component>>(pool);
            auto& component  = components[entityID];
            component.exists = true;
            return component;
        };

        template <typename component>
        component& getComponent(size_t entityID)
        {
            auto& components = std::get<std::vector<component>>(pool);
            auto& component  = components[entityID];
            return component;
        };

        template <typename component>
        bool hasComponent(size_t entityID)
        {
            auto& components = std::get<std::vector<component>>(pool);
            auto& component  = components[entityID];
            return component.exists;
        };

        const std::string& getTag(size_t entityID)
        {
            return tags[entityID];
        };
};
}
#define MemoryPool_()               EntityMemoryPool::getInstance()
#define AllocateEntity_(tag)        EntityMemoryPool::getInstance().allocateEntity(tag)
#define DeAllocateEntity(entityID)  EntityMemoryPool::getInstance().deallocateEntity(entityID)
#define TestEMP()                   EntityMemoryPool::getInstance()
