#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "ArchetypeManager.h"
#include "ComponentRegistry.h"
#include "EngineCore.h"
#include "Entity.h"

class EntityManager {
   public:
    EntityManager(ArchetypeManager& archetypeManager);
    ~EntityManager();

    void initialize();

    Entity::Handle createEntity();

    void destroyEntity(Entity::Handle entity);

    bool validEntity(Entity::Handle entity);

    template <typename ComponentType>
    void addComponent(Entity::Handle entity, ComponentType component);

    template <typename ComponentType>
    void removeComponent(Entity::Handle entity);

    Archetype& getArchetype(Entity::Handle entity);

   private:
    ArchetypeManager& archetypeManager;

    Entity::Type nextEntityID = 0;

    std::vector<Entity::Type> availableEntityIDs;
    std::vector<Entity::Type> activeEntityIDs;
    std::vector<Entity::Type> generations;

    std::unordered_map<Entity::Type, Entity::ComponentMask> entityMasks;
    std::unordered_map<Entity::Type, Archetype*> entityArchetypes;
};

template <typename ComponentType>
void EntityManager::addComponent(Entity::Handle entity, ComponentType component) {
    auto& oldMask = entityMasks[entity.id];

    std::cout << "[SYSTEM]::[ENTITYMANAGER] Entity: " << entity.id << " Adding component "
              << typeid(ComponentType).name() << std::endl;

    Entity::ComponentMask componentMask = ComponentRegistry::getInstance().getComponentMask<ComponentType>();

    if (componentMask == 0) {
        std::cerr << "[NOTICE]::[ENTITYMANAGER] Entity: " << entity.id
                  << " Component mask not found for type: " << typeid(ComponentType).name() << std::endl;
        return;
    }

    Entity::ComponentMask newMask = oldMask | componentMask;

    // Handle case where entity has no archetype yet
    if (!entityArchetypes[entity.id]) {
        std::cout << "[SYSTEM]::[ENTITYMANAGER] Entity: " << entity.id
                  << " has no archetype. Assigning to new archetype." << std::endl;

        // Create new archetype and assign the entity
        Archetype& newArchetype = archetypeManager.getOrCreateArchetype(newMask);
        newArchetype.entities.push_back(entity);
        newArchetype.addComponent(newArchetype.entities.size() - 1, std::move(component));

        // Update entity data
        entityArchetypes[entity.id] = &newArchetype;
        entityMasks[entity.id] = newMask;
        return;
    }

    auto& oldArchetype = *entityArchetypes[entity.id];
    auto it = std::find(oldArchetype.entities.begin(), oldArchetype.entities.end(), entity);
    if (it == oldArchetype.entities.end()) {
        std::cerr << "[FAILED]::[ENTITYMANAGER] Entity: " << entity.id << " Not found in old archetype (missing)"
                  << entity.id << std::endl;
        return;
    }

    size_t index = std::distance(oldArchetype.entities.begin(), it);

    // Step 1: Transfer components from old archetype to new archetype
    Archetype& newArchetype = archetypeManager.getOrCreateArchetype(newMask);
    oldArchetype.transferComponents(index, newArchetype);

    // Step 2: Remove the entity from the old archetype
    oldArchetype.entities.erase(it);

    // Step 3: Add the entity to the new archetype
    newArchetype.entities.push_back(entity);
    newArchetype.addComponent(newArchetype.entities.size() - 1, std::move(component));

    // Step 4: Update entity mappings
    entityArchetypes[entity.id] = &newArchetype;
    entityMasks[entity.id] = newMask;
}

template <typename ComponentType>
void EntityManager::removeComponent(Entity::Handle entity) {
    auto& oldMask = entityMasks[entity.id];

    Entity::ComponentMask componentMask = ComponentRegistry::getInstance().getComponentMask<ComponentType>();

    if (!(oldMask & componentMask)) {
        std::cerr << "[NOTICE]::[ENTITYMANAGER] Entity: " << entity.id << " Attempted to remove non-existing component"
                  << entity.id << typeid(ComponentType).name() << std::endl;
        return;
    }

    Entity::ComponentMask newMask = oldMask & ~componentMask;

    if (newMask != oldMask) {
        auto& oldArchetype = *entityArchetypes[entity.id];
        size_t index = std::distance(oldArchetype.entities.begin(),
                                     std::find(oldArchetype.entities.begin(), oldArchetype.entities.end(), entity));
        oldArchetype.entities.erase(oldArchetype.entities.begin() + index);

        Archetype& newArchetype = archetypeManager.getOrCreateArchetype(newMask);
        newArchetype.entities.push_back(entity);

        entityArchetypes[entity.id] = &newArchetype;
        entityMasks[entity.id] = newMask;
    }
}

#endif  // ENTITY_MANAGER_H
