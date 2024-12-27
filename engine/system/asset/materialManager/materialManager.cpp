#include "materialManager.h"


MaterialManager::MaterialManager(std::shared_ptr<ShaderManager> shaderManagerObj, std::shared_ptr<TextureManager> textureManagerObj) : shaderManager(shaderManagerObj), textureManager(textureManagerObj)
{
    Log_(Log::System, Log::mMaterial, "Initializing..");
    cacheMaterials();
    Log_(Log::System, Log::mMaterial, "initialized successfully!");

}

void MaterialManager::cacheMaterials()
{
    auto files = Toolkit::FileManager::getFiles(materialDirectory, ".json");

    for (auto& filepath : files)
    {
        std::string name = std::filesystem::path(filepath).stem().string();

        auto data = Toolkit::FileManager::loadJson(filepath);
        if (!data.empty())
        {
            loadMaterial(data["name"], data["shaderName"], data["textureName"]);
            Log_(Log::Trace, Log::mMaterial, "Caching {} material from with shader {} | texture {}", name, data["shaderName"], data["textureName"]);
        }
    }
}

std::shared_ptr<Material> MaterialManager::loadMaterial(const std::string name, const std::string shaderName, const std::string textureName)
{
    Log_(Log::System, Log::Texture, "Loading material: {}",  name);

    if (materialRegistry.find(name) != materialRegistry.end())
    {
        Log_(Log::Debug, Log::mTexture, "Material {} already created", name);
        return materialRegistry[name];
    }

    auto shader  = shaderManager->getShader(shaderName);
    if (!shader)
    {
        Log_(Log::Error, Log::mMaterial, "Shader not found: {}", shaderName);
        return nullptr;
    }

    auto texture = textureManager->getTexture(textureName);
    if (!texture)
    {
        Log_(Log::Error, Log::mMaterial, "Texture not found: {}", textureName);
        return nullptr;
    }

    auto material = std::make_shared<Material>(shader);
    material->setTextureUniform("uTexture", texture->getID());

    materialRegistry[name]= material;
    return material;    
}

std::shared_ptr<Material> MaterialManager::getMaterial(const std::string name) const
{
return std::shared_ptr<Material>();
}
 