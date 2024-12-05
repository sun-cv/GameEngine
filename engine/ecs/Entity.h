#ifndef ENTITY_H
#define ENTITY_H

#include "EngineCore.h"

namespace Entity {

using Type = std::size_t;
const Type INVALID_ENTITY = static_cast<Type>(-1);

struct Handle {
    Type id;
    Type generation;

    bool isValid() const { return id != INVALID_ENTITY; }
};

const Handle INVALID_HANDLE = {INVALID_ENTITY, 0};

inline bool operator==(const Handle& lhs, const Handle& rhs) {
    return lhs.id == rhs.id && lhs.generation == rhs.generation;
}

inline bool operator!=(const Handle& lhs, const Handle& rhs) { return !(lhs == rhs); }

using ComponentMask = Type;

// Hash Specialization (for unordered_map/unordered_set)
}  // namespace Entity

namespace std {
template <>
struct hash<Entity::Handle> {
    std::size_t operator()(const Entity::Handle& handle) const {
        return std::hash<Entity::Type>()(handle.id) ^ (std::hash<Entity::Type>()(handle.generation) << 1);
    }
};
}  // namespace std

#endif  // ENTITY_H
