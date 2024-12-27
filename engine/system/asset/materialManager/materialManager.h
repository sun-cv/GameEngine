#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include "ShaderManager.h"
#include "TextureManager.h"

#include "Material.h"

class MaterialManager
{
    private:
        std::string materialDirectory = "D:/Projects/Active/GameEngine/assets/materials";
        std::unordered_map<std::string, std::shared_ptr<Material>> materialRegistry;

        std::shared_ptr<ShaderManager>  shaderManager;
        std::shared_ptr<TextureManager> textureManager;

        void cacheMaterials();

    public:
        MaterialManager(std::shared_ptr<ShaderManager> shaderManager, std::shared_ptr<TextureManager> textureManager);

        std::shared_ptr<Material> loadMaterial  (const std::string name, const std::string shaderName, const std::string textureName);
        std::shared_ptr<Material> getMaterial   (const std::string name) const;
};


#endif