#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <optional>
#include "EngineCore.h"

struct TransformComponent {
    Vector3 position{0.0f, 0.0f, 0.0f};
    Vector3 rotation{0.0f, 0.0f, 0.0f};
    Vector3 scale{1.0f, 1.0f, 1.0f};
    Matrix4 worldMatrix = Matrix4(1.0f);
    Vector2 position;  // Screen position
    Vector2 size;      // Width, height
    float zOrder;      // Render order (higher = on top)
    std::optional<size_t> parentEntity;
};

#endif