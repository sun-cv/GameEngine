#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "ECSCore.h"
#include "EntityMemoryPool.h"
#include "Entity.h"

class EntityManager 
{
    private:
        std::vector<Entity>                     entities;
        std::vector<Entity>                     createQueue;
        std::vector<Entity>                     destroyQueue;

    public:
        EntityManager();                         
       ~EntityManager();

        Entity addEntity(const std::string & tag);


        void update();
        void createEntities();
        void destroyEntities();



};



#endif