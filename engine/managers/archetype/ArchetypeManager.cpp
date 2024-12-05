#include "ArchetypeManager.h"

ArchetypeManager::ArchetypeManager() { initialize(); }

void ArchetypeManager::initialize() {
    std::cout << "[SYSTEM]::[ARCHETYPEMANAGER] Starting Archetype Manager.." << std::endl;
    std::cout << "[SYSTEM]::[ARCHETYPEMANAGER] Loaded successfully" << std::endl;
}

Archetype& ArchetypeManager::getOrCreateArchetype(const Entity::ComponentMask& mask) {
    auto iterator = archetypes.find(mask);
    if (iterator == archetypes.end()) {
        auto archetype = std::make_unique<Archetype>();
        auto& ref = *archetype;
        archetypes[mask] = std::move(archetype);
        return ref;
    }
    return *iterator->second;
}

std::vector<Archetype*> ArchetypeManager::getArchetypesMatchingMask(const Entity::ComponentMask& mask) const {
    std::vector<Archetype*> matchingArchetypes;

    for (const auto& [key, archetype] : archetypes) {
        if ((key & mask) == mask) {
            matchingArchetypes.push_back(archetype.get());
        }
    }

    return matchingArchetypes;
}
