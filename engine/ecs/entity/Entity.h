#ifndef ENTITY_H
#define ENTITY_H

#include "CoreECS.h"
#include "EntityMemoryPool.h"

class EntityMemoryPool;

namespace ECS
{
class Entity
{
    private:
        size id;
    
    public:
        Entity(size id) : id(id) {};
        
        template<typename component>
        component & getComponent()
        {
            return EntityMemoryPool::Instance().getComponent<component>(id);
        }

        template<typename component>
        bool hasComponent()
        {
            return EntityMemoryPool::Instance().hasComponent<component>(id);
        }

        size getID()
        {
            return id;
        }

        bool isValid()
        {
            return id != INVALID_ENTITY;
        }

        bool operator == (const Entity& other) const 
        {
            return id == other.id;
        }

        bool operator != (const Entity& other) const 
        { 
            return !(*this == other);
        }
};
}

#endif