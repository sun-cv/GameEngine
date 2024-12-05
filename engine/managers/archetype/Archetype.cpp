#include "Archetype.h"

void Archetype::transferComponents(Entity::Type entityIndex, Archetype& targetArchetype) {
    for (auto& [type, array] : componentArrays) {
        auto& targetArray = targetArchetype.componentArrays[type];
        size_t componentSize = array.size() / entities.size();

        // Ensure the target array has enough space
        if (targetArray.size() < (entityIndex + 1) * componentSize) {
            targetArray.resize((entityIndex + 1) * componentSize);
        }

        // Transfer component data to the target array
        std::memcpy(&targetArray[entityIndex * componentSize], &array[entityIndex * componentSize], componentSize);

        // Optionally clear the original data in the source array
        std::memset(&array[entityIndex * componentSize], 0, componentSize);
    }
}
