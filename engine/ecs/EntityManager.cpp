#include "EntityManager.h"

EntityManager::EntityManager(ArchetypeManager& archetypeManager) : archetypeManager(archetypeManager) { initialize(); }

EntityManager::~EntityManager() {
    // ENTITY DESTRUCTION REWORK REQUIRED
    std::cout << "[SYSTEM]::[ENTITYMANAGER] Destroying all entities" << std::endl;
}

void EntityManager::initialize() {
    // initialization
    std::cout << "[SYSTEM]::[ENTITYMANAGER] Starting Entity Manager.." << std::endl;
    std::cout << "[SYSTEM]::[ENTITYMANAGER] Loaded successfully" << std::endl;
}

Entity::Handle EntityManager::createEntity() {
    Entity::Type id;

    if (availableEntityIDs.empty()) {
        id = nextEntityID++;
        generations.push_back(0);
        std::cout << "[SYSTEM]::[ENTITYMANAGER] Entity: " << id << " created successfully" << std::endl;
    } else {
        id = availableEntityIDs.back();
        availableEntityIDs.pop_back();
        std::cout << "[SYSTEM]::[ENTITYMANAGER] Entity: " << id << " re-used :: Generation: " << generations[id]
                  << std::endl;
    }

    activeEntityIDs.push_back(id);
    entityMasks[id] = 0;
    return {id, generations[id]};
}

void EntityManager::destroyEntity(Entity::Handle entity) {
    if (!validEntity(entity)) {
        std::cout << "[BROKEN]::[ENTITYMANAGER] Invalid entity: " << entity.id << std::endl;
        return;
    }

    Archetype* archetype = entityArchetypes[entity.id];
    if (archetype) {
        auto iterator = std::find(archetype->entities.begin(), archetype->entities.end(), entity);
        if (iterator != archetype->entities.end()) {
            size_t index = std::distance(archetype->entities.begin(), iterator);
            archetype->entities.erase(iterator);
        }
    }

    entityMasks.erase(entity.id);
    entityArchetypes.erase(entity.id);

    generations[entity.id]++;

    auto activeIt = std::find(activeEntityIDs.begin(), activeEntityIDs.end(), entity.id);
    if (activeIt != activeEntityIDs.end()) {
        activeEntityIDs.erase(activeIt);
    }

    // Add the ID to available entities
    availableEntityIDs.push_back(entity.id);

    std::cout << "[SYSTEM]::[ENTITYMANAGER] Entity: " << entity.id << " recycled successfully" << std::endl;
}

bool EntityManager::validEntity(Entity::Handle entity) {
    return entity.id < generations.size() && generations[entity.id] == entity.generation;
}

Archetype& EntityManager::getArchetype(Entity::Handle entity) {
    if (entityArchetypes.find(entity.id) == entityArchetypes.end()) {
        std::cout << "[FAILURE]::[ENTITYMANAGER] Entity: " << entity.id
                  << " Does not belong to any archetype: " << std::endl;
    }

    return *entityArchetypes[entity.id];
}
