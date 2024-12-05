#ifndef ARCHETYPE_H
#define ARCHETYPE_H

#include <cstddef>
#include <typeindex>
#include "EngineCore.h"
#include "Entity.h"

class Archetype {
   public:
    // Stores entity handles associated with this archetype
    std::vector<Entity::Handle> entities;

    // Add a component to an entity
    template <typename ComponentType>
    void addComponent(Entity::Type entityIndex, ComponentType component);

    // Get a mutable pointer to a component
    template <typename ComponentType>
    ComponentType* getComponent(Entity::Type entityIndex);

    // Get a const pointer to a component
    template <typename ComponentType>
    const ComponentType* getComponent(Entity::Type entityIndex) const;

    // Remove a component from an entity
    template <typename ComponentType>
    void removeComponent(Entity::Type entityIndex);

    // Transfer components from this archetype to another
    void transferComponents(Entity::Type entityIndex, Archetype& targetArchetype);

   private:
    // Maps component types to their respective byte arrays
    std::unordered_map<std::type_index, std::vector<std::byte>> componentArrays;

    // Utility function to ensure component storage is large enough
    template <typename ComponentType>
    void ensureComponentStorage(Entity::Type entityIndex);
};

// Implementation of templated methods

template <typename ComponentType>
void Archetype::addComponent(Entity::Type entityIndex, ComponentType component) {
    ensureComponentStorage<ComponentType>(entityIndex);
    auto& array = componentArrays[std::type_index(typeid(ComponentType))];
    new (&array[entityIndex * sizeof(ComponentType)]) ComponentType(std::move(component));
}

template <typename ComponentType>
ComponentType* Archetype::getComponent(Entity::Type entityIndex) {
    auto it = componentArrays.find(std::type_index(typeid(ComponentType)));
    if (it == componentArrays.end()) return nullptr;

    auto& array = it->second;
    if (array.size() <= entityIndex * sizeof(ComponentType)) return nullptr;

    return reinterpret_cast<ComponentType*>(&array[entityIndex * sizeof(ComponentType)]);
}

template <typename ComponentType>
const ComponentType* Archetype::getComponent(Entity::Type entityIndex) const {
    auto it = componentArrays.find(std::type_index(typeid(ComponentType)));
    if (it == componentArrays.end()) return nullptr;

    const auto& array = it->second;
    if (array.size() <= entityIndex * sizeof(ComponentType)) return nullptr;

    return reinterpret_cast<const ComponentType*>(&array[entityIndex * sizeof(ComponentType)]);
}

template <typename ComponentType>
void Archetype::removeComponent(Entity::Type entityIndex) {
    auto it = componentArrays.find(std::type_index(typeid(ComponentType)));
    if (it == componentArrays.end()) return;

    auto& array = it->second;
    if (array.size() <= entityIndex * sizeof(ComponentType)) return;

    reinterpret_cast<ComponentType*>(&array[entityIndex * sizeof(ComponentType)])->~ComponentType();
}

template <typename ComponentType>
void Archetype::ensureComponentStorage(Entity::Type entityIndex) {
    auto& array = componentArrays[std::type_index(typeid(ComponentType))];
    if (array.size() < (entityIndex + 1) * sizeof(ComponentType)) {
        array.resize((entityIndex + 1) * sizeof(ComponentType));
    }
}

#endif  // ARCHETYPE_H
