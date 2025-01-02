#pragma once

#include "CoreUtility.h"
#include "CoreToolkit.h"

#include "ShaderManager.h"
#include "TextureManager.h"
#include "Material.h"

#include <nlohmann/json.hpp>

class MaterialManager
{
    private:
        std::string materialDirectory = "D:/Projects/Active/GameEngine/assets/material";
        std::unordered_map<std::string, std::shared_ptr<Material>> materialRegistry;

        std::shared_ptr<ShaderManager>  shaderManager;
        std::shared_ptr<TextureManager> textureManager;
    private:
        void cacheMaterials();
        void parseUniforms(std::shared_ptr<Material> material, nlohmann::json data);

    public:
        MaterialManager(std::shared_ptr<ShaderManager> shaderManager, std::shared_ptr<TextureManager> textureManager);

        std::shared_ptr<Material> loadMaterial  (const std::string name, const std::string shaderName, const std::string textureName, nlohmann::json data);
        std::shared_ptr<Material> getMaterial   (const std::string name) const;
};
