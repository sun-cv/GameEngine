#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "CoreEngine.h"
#include "CoreECS.h"

namespace ECS
{
class EntityManager 
{
    private:
        std::vector<Entity>                     entities;
        std::vector<Entity>                     createQueue;
        std::vector<Entity>                     destroyQueue;

    public:
        EntityManager();                         
       ~EntityManager();

        Entity addEntity    (const std::string & tag);
        void destroyEntity  (Entity entity);

        void update();
        void createEntities ();
        void destroyEntities();

        std::vector<Entity> getEntities();


};
}


#endif