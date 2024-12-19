#ifndef ENTITY_H
#define ENTITY_H

#include "ECSCore.h"

class EntityMemoryPool;

class Entity
{
    private:
        ECS::Type id;
    public:
        Entity(ECS::Type id) : id(id) {};
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

        ECS::Type getID()
        {
            return id;
        }

        bool isValid()
        {
            return id != ECS::INVALID_ENTITY;
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

#endif