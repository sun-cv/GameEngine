#include "MaterialManager.h"


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
            loadMaterial(data["name"], data["shaderName"], data["textureName"], data);
            Log_(Log::Trace, Log::mMaterial, "Caching {} material with shader {} | texture {}", name, data["shaderName"], data["textureName"]);
        }
    }
}


void MaterialManager::parseUniforms(std::shared_ptr<Material> material, nlohmann::json data)
{
    if (!data.contains("uniforms"))
    {
        Log_(Log::Debug, Log::mFile, "uniforms not present in JSON"); 
        return;
    }   

    for (const auto& uniforms : data["uniforms"])
        { 
            std::string type = uniforms["type"];
            Log_(Log::Trace, Log::mMaterial, "Setting uniform {}s | {}", type, uniforms["uniforms"].size());
            if (type == "int" && uniforms["uniforms"].size() > 0 )
            {
                for (const auto& element : uniforms["uniforms"])
                {
                    std::string  uniform = element["uniform"].get<std::string>();
                    int          value   = element["value"]  .get<int>();
                    material->setUniform(uniform, value);
                }
            }
            else if (type == "float" && uniforms["uniforms"].size() > 0 )
            {
                for (const auto& element : uniforms["uniforms"])
                {
                    std::string  uniform = element["uniform"].get<std::string>();
                    float        value   = element["value"]  .get<float>();
                    material->setUniform(uniform, value);
                }
            }
            else if (type == "vec3" && uniforms["uniforms"].size() > 0 )
            {
                for (const auto& element : uniforms["uniforms"])
                {
                    std::string  uniform = element["uniform"].get<std::string>();
                    glm::vec3    value   = element["value"]  .get<glm::vec3>();
                    material->setUniform(uniform, value);
                }
            }
            else if (type == "vec4" && uniforms["uniforms"].size() > 0 )
            {
                for (const auto& element : uniforms["uniforms"])
                {
                    std::string  uniform = element["uniform"].get<std::string>();
                    glm::vec4    value   = element["value"]  .get<glm::vec4>();

                    material->setUniform(uniform, value);
                }
            }
            else if (type == "mat4" && uniforms["uniforms"].size() > 0 )
            {
                for (const auto& element : uniforms["uniforms"])
                {
                    std::string  uniform = element["uniform"].get<std::string>();
                    glm::mat4    value   = element["value"]  .get<glm::mat4>();
                    material->setUniform(uniform, value);
                }
            }
            else if (type == "texture" && uniforms["uniforms"].size() > 0  )
            {
                for (const auto& element : uniforms["uniforms"])
                {
                    std::string  uniform = element["uniform"].get<std::string>();
                    int          value   = element["value"]  .get<int>();
                    material->setTextureUniform(uniform, value);
                }
            }
            else if (uniforms["uniforms"].size() == 0)
            {
                Log_(Log::Trace, Log::mFile, "No uniforms present for {}", type); 
            }
            else
            {
                Log_(Log::Error, Log::mFile, "Unknown type in uniform parse: {}", type); 
            }
        } 
}

std::shared_ptr<Material> MaterialManager::loadMaterial(const std::string name, const std::string shaderName, const std::string textureName, nlohmann::json data )
{
    Log_(Log::Debug, Log::Material, "Loading material: {}",  name);

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
    material->addTexture(texture); 
    parseUniforms(material, data);  

    auto shadername = shader->getName();
    materialRegistry[name]= material;
    return material;    
}

std::shared_ptr<Material> MaterialManager::getMaterial(const std::string name) const
{
    auto iterator = materialRegistry.find(name);
    if (iterator != materialRegistry.end())
    {
        return iterator->second;
    }

    Log_(Log::Warning, Log::mMaterial, "Material {} not found. Falling back to default material");

    auto defaultIterator = materialRegistry.find("default");
    if (defaultIterator != materialRegistry.end()) 
    {
        return defaultIterator->second;
    }

    Log_(Log::Fatal, Log::mTexture, "Default material is missing!");
    return nullptr;
}
 