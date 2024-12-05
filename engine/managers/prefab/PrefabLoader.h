#ifndef PREFAB_LOADER_H
#define PREFAB_LOADER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "EngineCore.h"
#include "EntityManager.h"
#include "FileManager.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "materialManager.h"

class PrefabLoader {
   public:
    PrefabLoader(EntityManager& entityManager, MeshManager& meshManager, MaterialManager& materialManager);

    void initialize();
    void preloadPrefabs(const std::string& prefabDirectory);
    Entity::Handle createInstance(const std::string& prefabName);

   private:
    struct PrefabData {
        nlohmann::json jsonData;

        // Default constructor
        PrefabData() = default;

        // Constructor to accept JSON data
        explicit PrefabData(const nlohmann::json& json) : jsonData(json) {}
    };

    EntityManager& entityManager;
    MeshManager& meshManager;
    MaterialManager& materialManager;

    std::unordered_map<std::string, std::string> prefabPaths;
    std::unordered_map<std::string, PrefabData> prefabCache;

    std::string prefabDirectory = "D:/Projects/GameEngine/assets/prefabs";
};

#endif
