#include "RenderSystem.h"

RenderSystem::RenderSystem(Renderer& renderer, ArchetypeManager& archetypeManager, OverlaySystem& overlaySystem)
    : renderer(renderer), archetypeManager(archetypeManager), overlaySystem(overlaySystem) {
    initialize();
}

void RenderSystem::initialize() {
    std::cout << "[SYSTEM]::[RENDERSYSTEM] Starting Render System.." << std::endl;
    std::cout << "[SYSTEM]::[RENDERSYSTEM] Loaded successfully" << std::endl;
}

void RenderSystem::setViewProjection(const glm::mat4& view, const glm::mat4& projection) {
    viewMatrix = view;
    projectionMatrix = projection;
}

void RenderSystem::render() {
    renderer.clear(clearScreen);

    batchRenderEntities(groupEntities());
    batchRenderOverlays(groupOverlays());
}

RenderSystem::EntityGroup RenderSystem::groupEntities() {
    EntityGroup groupedEntities;

    auto combinedMask =
        ComponentRegistry::getInstance().getCombinedMask<RenderableComponent, MaterialComponent, TransformComponent>();

    const auto& archetypes = archetypeManager.getArchetypesMatchingMask(combinedMask);

    for (const auto* archetype : archetypes) {
        for (const auto& entity : archetype->entities) {
            const auto* renderable = archetype->getComponent<RenderableComponent>(entity.id);
            const auto* material = archetype->getComponent<MaterialComponent>(entity.id);
            const auto* transform = archetype->getComponent<TransformComponent>(entity.id);

            if (!renderable || !material || !transform) {
                std::cout << "[NOTICE]::[RENDERSYSTEM] Missing component for Entity ID: " << entity.id << "\n";
                continue;
            }

            groupedEntities[{renderable->mesh, const_cast<MaterialComponent*>(material)}].emplace_back(
                transform->worldMatrix, entity);
        }
    }

    return groupedEntities;
}

RenderSystem::OverlayGroup RenderSystem::groupOverlays() {
    OverlayGroup groupedLayers;
    groupedLayers = overlaySystem.getOverlayLayers();

    return groupedLayers;
}

void RenderSystem::batchRenderEntities(const EntityGroup& entityGroups) {
    for (const auto& [key, instances] : entityGroups) {
        auto* mesh = key.first;
        auto* material = key.second;

        if (!material || !material->shader) {
            std::cerr << "[FAILURE] Material has no shader. Skipping render.\n";
            continue;
        }

        std::vector<Mesh*> meshes;
        std::vector<glm::mat4> transforms;

        for (const auto& [transform, entity] : instances) {
            meshes.push_back(mesh);
            transforms.push_back(transform);
        }

        renderer.renderBatch(meshes, *material, transforms);
    }
}

void RenderSystem::batchRenderOverlays(const OverlayGroup& overlayGroups) {
    const auto& overlayLayers = overlaySystem.getOverlayLayers();

    for (const auto& [zIndex, layer] : overlayGroups) {
        for (const auto& element : layer.elements) {
            for (const auto& text : element.textComponents) {
                renderer.renderText(text);
            }
            // Render HUD components
            // for (const auto& hud : element.hudComponents) {
            //     renderer.renderHUD(hud);
            // }
        }
    }
}
