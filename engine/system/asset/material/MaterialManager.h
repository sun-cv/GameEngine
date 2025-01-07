#pragma once

#include <variant>

#include "CoreUtility.h"
#include "CoreToolkit.h"
#include "CoreMath.h"

#include "ShaderManager.h"
#include "TextureManager.h"
#include "Material.h"



#include <nlohmann/json.hpp>

class MaterialManager
{   // Variables
    private: // Dependencies
        std::shared_ptr<ShaderManager>          shaderManager;
        std::shared_ptr<TextureManager>         textureManager;

        std::string materialDirectory           = "D:/Projects/Active/GameEngine/assets/material";
        
        std::unordered_map<
            std::string,
            std::shared_ptr<Material>
        >                                       materialRegistry;

    
    // Functions
    private: // Initialization
        void cacheMaterials();
    
            // Helper
        void loadMaterialData(std::string name, std::string filepath);
        void parseUniforms   (std::shared_ptr<Material> material, nlohmann::json data);

    public: // Access
        std::shared_ptr<Material> loadMaterial  (const std::string name, const std::string shaderName, const std::string textureName, nlohmann::json data);
        std::shared_ptr<Material> getMaterial   (const std::string name) const;
            // Release
        void removeMaterial(std::string name);
        void clear();

    public:
        MaterialManager(std::shared_ptr<ShaderManager> shaderManager, std::shared_ptr<TextureManager> textureManager);
       ~MaterialManager();
};
