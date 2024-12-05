#include "PrefabLoader.h"

PrefabLoader::PrefabLoader(EntityManager& entityManager, MeshManager& meshManager, MaterialManager& materialManager)
    : entityManager(entityManager), meshManager(meshManager), materialManager(materialManager) {
    initialize();
}

void PrefabLoader::initialize() {
    std::cout << "[SYSTEM]::[PREFABLOADER] Starting Prefab Loader.." << std::endl;
    preloadPrefabs(prefabDirectory);
    std::cout << "[SYSTEM]::[PREFABLOADER] Prefabs loaded from: " << prefabDirectory << "\n";
}

void PrefabLoader::preloadPrefabs(const std::string& directory) {
    for (const auto& filePath : FileManager::getFiles(directory, ".json")) {
        std::string prefabName = std::filesystem::path(filePath).stem().string();
        auto jsonData = FileManager::loadJson(filePath);

        if (!jsonData.empty()) {
            prefabPaths[prefabName] = filePath;
            prefabCache.emplace(prefabName, PrefabData(std::move(jsonData)));
            std::cout << "[SYSTEM]::[PREFABLOADER] Prefab cached: " << prefabName << " :: File Path: " << filePath
                      << std::endl;
        }
    }
}

Entity::Handle PrefabLoader::createInstance(const std::string& prefabName) {
    if (prefabCache.find(prefabName) == prefabCache.end()) {
        std::cerr << "[NOTICE]::[PREFABLOADER] Prefab missing: " << prefabName << std::endl;
        return {Entity::INVALID_ENTITY, 0};
    }

    const auto& prefabData = prefabCache[prefabName].jsonData;
    Entity::Handle entity = entityManager.createEntity();

    RenderableComponent renderableComponent;
    TransformComponent transformComponent;

    std::shared_ptr<Mesh> mesh = nullptr;
    if (prefabData.contains("meshName")) {
        std::string meshName = prefabData["meshName"];
        mesh = meshManager.getMeshByName(meshName);

        if (!mesh) {
            std::cout << "[NOTICE]::[PREFABLOADER] Mesh missing. Attempting to load: " << meshName << std::endl;
            mesh = meshManager.loadMesh(meshName, prefabDirectory + "/mesh/" + meshName + ".json");

            if (!mesh) {
                std::cerr << "[FAILED]::[PREFABLOADER] Failed to load mesh: " << meshName << std::endl;
                return {Entity::INVALID_ENTITY, 0};
            }
        }
    } else {
        std::cerr << "[NOTICE]::[PREFABLOADER] Mesh not defined for prefab: " << prefabName << std::endl;
        return {Entity::INVALID_ENTITY, 0};
    }

    renderableComponent.mesh = mesh.get();

    std::string shaderName = prefabData.contains("shaderName") ? prefabData["shaderName"] : "";
    std::string textureName = prefabData.contains("textureName") ? prefabData["textureName"] : "";

    auto material = materialManager.createMaterial(prefabName, shaderName, textureName);
    if (!material) {
        std::cerr << "[FAILED]::[PREFABLOADER] Failed to create material for prefab: " << prefabName << std::endl;
        return {Entity::INVALID_ENTITY, 0};
    }

    // Set Uniforms (optional)
    if (prefabData.contains("uniforms")) {
        const auto& uniforms = prefabData["uniforms"];
        if (uniforms.contains("color")) {
            const auto& colorArray = uniforms["color"];
            glm::vec3 color(colorArray[0], colorArray[1], colorArray[2]);
            material->setUniform("color", color);
        }
    }

    // Add TransformComponent
    if (prefabData.contains("transform")) {
        const auto& transformData = prefabData["transform"];
        if (transformData.contains("position"))
            transformComponent.position =
                glm::vec3(transformData["position"][0], transformData["position"][1], transformData["position"][2]);
        if (transformData.contains("rotation"))
            transformComponent.rotation =
                glm::vec3(transformData["rotation"][0], transformData["rotation"][1], transformData["rotation"][2]);
        if (transformData.contains("scale"))
            transformComponent.scale =
                glm::vec3(transformData["scale"][0], transformData["scale"][1], transformData["scale"][2]);
    }

    // Add Components to Entity
    entityManager.addComponent<RenderableComponent>(entity, renderableComponent);
    entityManager.addComponent<MaterialComponent>(entity, *material);
    entityManager.addComponent<TransformComponent>(entity, transformComponent);

    std::cout << "[SYSTEM]::[PREFABLOADER] Prefab created: " << prefabName << " ID: " << entity.id << std::endl;
    return entity;
}
