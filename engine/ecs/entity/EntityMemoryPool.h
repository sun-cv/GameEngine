#ifndef ENTITY_MEMORY_POOL_H
#define ENTITY_MEMORY_POOL_H

#include "CoreEngine.h"
#include "CoreECS.h"

namespace ECS 
{
class EntityMemoryPool
{
    private:
        EntityMemoryPool();

        ECS::VectorTuple                        pool;
        
        ECS::size                               totalEntities;
        std::vector<std::string>                tags;    
        std::vector<bool>                       active;

        void initializeEntity       (size entityID, const std::string& tag);
        
    public: 
        EntityMemoryPool            (const EntityMemoryPool &) = delete;
        EntityMemoryPool &operator= (const EntityMemoryPool &) = delete;

        size getNextEntityIndex     ();
        size allocateEntity         (const std::string& tag);
        void deallocateEntity       (size entityID);
        
        static EntityMemoryPool&    getInstance()
        {
            static EntityMemoryPool instance;
            return instance;
        }

    private:

        template<typename component>
        void initializeVector(std::vector<component>& vector)
        {
            vector.resize(MAX_ENTITIES);
            Log_(Log::Trace, Log::EMP, "Instantiated entity limit {} vector of {}", vector.size(), typeid(component).name());
        }

        template<size index = 0, size count>
        typename std::enable_if<index == count, void>::type
        initializeComponents(VectorTuple&)
        {

        }

        template<size index = 0, size count>
        typename std::enable_if<index <  count, void>::type
        initializeComponents(VectorTuple& tuple)
        {
            initializeVector(std::get<index>(tuple));
            initializeComponents<index + 1, count>(tuple);
        }

        template <typename component>
        void resetComponent(VectorTuple& tuple, size entityID)
        {
            auto& components = std::get<std::vector<component>>(tuple);
            components[entityID] = component();
            Log_(Log::Trace, Log::EMP, "Reset component existence {} of {}", components[entityID].exists, typeid(component).name());
        }

    public:

        template <typename component>
        component& getComponent(size entityID)
        {
            return std::get<std::vector<component>>(pool)[entityID];
        }

        const std::string& getTag(size entityID)
        {
            return tags[entityID];
        }


        
};
}

#define MemoryPool_()               ECS::EntityMemoryPool::getInstance()
#define AllocateEntity_(tag)        ECS::EntityMemoryPool::getInstance().allocateEntity(tag)
#define DeAllocateEntity(entityID)  ECS::EntityMemoryPool::getInstance().deallocateEntity(entityID)

#endif