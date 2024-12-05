#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Core Identifiers
using EntityID = size_t;
using ComponentID = size_t;
using SystemID = size_t;

// Core Types
using Vector2 = glm::vec2;
using Vector3 = glm::vec3;
using Matrix4 = glm::mat4;
using Color = glm::vec4;

// Core Enums

// Core Constants
constexpr size_t MAX_ENTITIES = 10000;
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
constexpr std::string_view DEFAULT_SHADER_PATH = "assets/shaders/";
constexpr Color COLOR_WHITE = {1.0f, 1.0f, 1.0f, 1.0f};

// Utility Functions
inline float clamp(float value, float min, float max) { return std::max(min, std::min(value, max)); }

#endif  // ENGINE_CORE_H
