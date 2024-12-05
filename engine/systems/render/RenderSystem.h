#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <functional>
#include <glm/glm.hpp>
#include <utility>

#include "Archetype.h"
#include "ArchetypeManager.h"
#include "ComponentRegistry.h"
#include "EngineCore.h"
#include "MaterialComponent.h"
#include "Mesh.h"
#include "OverlayElement.h"
#include "OverlaySystem.h"
#include "RenderableComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>()(pair.first);
        auto hash2 = std::hash<T2>()(pair.second);
        return hash1 ^ (hash2 << 1);
    }
};

class RenderSystem {
   public:
    RenderSystem(Renderer& renderer, ArchetypeManager& archetypeManager, OverlaySystem& overlaySystem);
    void initialize();
    void setViewProjection(const glm::mat4& view, const glm::mat4& projection);
    void render();

   private:
    ArchetypeManager& archetypeManager;
    OverlaySystem& overlaySystem;
    Renderer& renderer;

    // Variables
    glm::vec4 clearScreen = {0.0f, 0.0f, 0.0f, 1.0f};

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    // Batch Render
    using EntityGroup = std::unordered_map<std::pair<Mesh*, MaterialComponent*>,
                                           std::vector<std::pair<glm::mat4, Entity::Handle>>, PairHash>;
    using OverlayGroup = std::map<int, OverlayLayer>;

    EntityGroup groupEntities();
    OverlayGroup groupOverlays();

    void batchRenderEntities(const EntityGroup& entityGroups);
    void batchRenderOverlays(const OverlayGroup& overlayGroups);
};

#endif