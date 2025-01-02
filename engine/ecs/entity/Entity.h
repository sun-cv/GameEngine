#pragma once

#include <cstddef>

#include "ECSValue.h"
#include "EntityMemoryPool.h"

namespace ECS
{
class Entity {
private:
    size id;

public:
    Entity(size id) : id(id) {}

    template <typename component>
    component& add() {
        return EntityMemoryPool::getInstance().template addComponent<component>(id);
    }

    template <typename component>
    component& get() {
        return EntityMemoryPool::getInstance().template getComponent<component>(id);
    }

    template <typename component>
    bool has() {
        return EntityMemoryPool::getInstance().template hasComponent<component>(id);
    }

    size getID() { return id; }

    bool isValid() { return id != INVALID_ENTITY; }

    bool operator==(const Entity& other) const { return id == other.id; }

    bool operator!=(const Entity& other) const { return !(*this == other); }
};
}
