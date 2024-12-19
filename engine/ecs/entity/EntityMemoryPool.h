#ifndef ENTITY_MEMORY_POOL_H
#define ENTITY_MEMORY_POOL_H

#include "EngineCore.h"
#include "ECScore.h"
#include "EngineVariables.h"

class Entity;

class EntityMemoryPool
{
    private:
        EntityMemoryPool();

        ECS::EntityComponentVectorTuple         pool;
        
        ECS::Type                               totalEntities;
        std::vector<std::string>                tags;    
        std::vector<bool>                       active;

        template<typename component>
        void initializeVector(std::vector<component>& vector)
        {
            vector.resize(MAX_ENTITIES);
            Log_(Log::Debug, Log::EMP, "Instantiated entity limit {} vector of {}", vector.size(), typeid(component).name());
        }

        template<ECS::Type index = 0, ECS::Type count>
        typename std::enable_if<index == count, void>::type
        initializeComponents(ECS::EntityComponentVectorTuple&)
        {

        }

        template<ECS::Type index = 0, ECS::Type count>
        typename std::enable_if<index < count, void>::type
        initializeComponents(ECS::EntityComponentVectorTuple& tuple)
        {
            initializeVector(std::get<index>(tuple));
            initializeComponents<index + 1, count>(tuple);
        }

        template <typename component>
        void resetComponent(ECS::EntityComponentVectorTuple& tuple, ECS::Type entityID)
        {
            std::vector test = std::get<std::vector<component>>(tuple);
            test[entityID] = component();
            Log_(Log::Debug, Log::EMP, "Reset component existence {} of {}", test[entityID].exists, typeid(component).name());
        }
        
        void initializeEntity(ECS::Type entityID, const std::string& tag);

    public: 
        EntityMemoryPool(const EntityMemoryPool &)              = delete;
        EntityMemoryPool &operator=(const EntityMemoryPool &)   = delete;

        static EntityMemoryPool& getInstance()
        {
            static EntityMemoryPool instance;
            return instance;
        }


        template <typename component>
        component& getComponent(ECS::Type entityID)
        {
            return std::get<std::vector<component>>(pool)[entityID];
        }

        const std::string& getTag(ECS::Type entityID)
        {
            return tags[entityID];
        }


        ECS::Type getNextEntityIndex();

        ECS::Type allocateEntity(const std::string& tag);

        
};

#define MemoryPool_()           EntityMemoryPool::getInstance();
#define AllocateEntity_(tag)    EntityMemoryPool::getInstance().allocateEntity(tag)

#endif