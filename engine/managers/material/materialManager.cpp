#include "MaterialManager.h"

MaterialManager::MaterialManager(ShaderManager& shaderManager, TextureManager& textureManager)
    : shaderManager(shaderManager), textureManager(textureManager) {}

std::shared_ptr<MaterialComponent> MaterialManager::createMaterial(const std::string& name,
                                                                   const std::string& shaderName,
                                                                   const std::string& textureName) {
    if (materials.find(name) != materials.end()) {
        std::cout << "[NOTICE]::[MATERIALMANAGER] Material already exists: " << name << std::endl;
        return materials[name];
    }

    auto shader = shaderManager.getShader(shaderName);
    if (!shader) {
        std::cerr << "[FAILED]::[MATERIALMANAGER] Shader not found: " << shaderName << std::endl;
        return nullptr;
    }

    auto material = std::make_shared<MaterialComponent>();
    material->shader = shader;
    material->shaderName = shaderName;

    auto texture = !textureName.empty() ? textureManager.getTextureByName(textureName)
                                        : textureManager.getTextureByName("default");

    if (texture) {
        material->setTextureUniform("texture1", texture->getID());
        if (textureName.empty()) {
            std::cout << "[NOTICE]::[MATERIALMANAGER] Texture not provided; using default.\n";
        }
    } else {
        std::cerr << "[FAILED]::[MATERIALMANAGER] Texture not found: "
                  << (textureName.empty() ? "default" : textureName) << std::endl;
    }

    std::cout << "[SYSTEM]::[MATERIALMANAGER] Created Material: " << name << std::endl;
    materials[name] = material;
    return material;
}

std::shared_ptr<MaterialComponent> MaterialManager::getMaterial(const std::string& name) const {
    auto it = materials.find(name);
    return (it != materials.end()) ? it->second : nullptr;
}
