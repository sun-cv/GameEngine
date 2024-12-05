#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include "EngineCore.h"
#include "MaterialComponent.h"
#include "ShaderManager.h"
#include "TextureManager.h"

class MaterialManager {
   public:
    explicit MaterialManager(ShaderManager& shaderManager, TextureManager& textureManager);

    // Create or retrieve a material by name
    std::shared_ptr<MaterialComponent> createMaterial(const std::string& name, const std::string& shaderName,
                                                      const std::string& textureName = "");

    // Retrieve an existing material by name
    std::shared_ptr<MaterialComponent> getMaterial(const std::string& name) const;

   private:
    ShaderManager& shaderManager;
    TextureManager& textureManager;

    // Map of material names to their corresponding material components
    std::unordered_map<std::string, std::shared_ptr<MaterialComponent>> materials;
};

#endif  // MATERIAL_MANAGER_H
