#ifndef ARCHETYPE_MANAGER_H
#define ARCHETYPE_MANAGER_H

#include "Archetype.h"
#include "EngineCore.h"


class ArchetypeManager {
   public:
    ArchetypeManager();

    void initialize();

    // Get an existing archetype for a specific component mask or create a new one
    Archetype& getOrCreateArchetype(const Entity::ComponentMask& mask);

    // Get all archetypes that match a given component mask
    std::vector<Archetype*> getArchetypesMatchingMask(const Entity::ComponentMask& mask) const;

   private:
    // Maps component masks to archetypes
    std::unordered_map<Entity::ComponentMask, std::unique_ptr<Archetype>> archetypes;
};

#endif  // ARCHETYPE_MANAGER_H
