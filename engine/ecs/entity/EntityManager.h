#pragma once

#include "CoreUtility.h"
#include "ECSValue.h"

#include "EntityMemoryPool.h"


namespace ECS
{
class EntityManager 
{   // Variables  
    private:
            // Memory allocation
        std::shared_ptr<EntityMemoryPool>       entityMemoryPool;
        
    public: // NA

    //Functions
    private:// NA
    public:
            // Entity Management
        Entity  createEntity  ();
        bool    validate(Entity entityID);
        void    destroy (Entity entityID);
        void    tag     (Entity entityID, std::string tag);

            // External access
        const std::vector<Entity> getEntities();
        const std::vector<Entity> getDirtyEntities();
        const std::vector<Entity>& getTag();


    public:
        EntityManager(std::shared_ptr<EntityMemoryPool> EntityMemoryPool);                         
       ~EntityManager();
};
}
