#include "MaterialManager.h"

#include <nlohmann/json.hpp>


MaterialManager::MaterialManager(std::shared_ptr<ShaderManager> shaderManagerObj, std::shared_ptr<TextureManager> textureManagerObj) : shaderManager(shaderManagerObj), textureManager(textureManagerObj)
{
    LogStartup(Log::mMaterial);
    try
    {
        cacheMaterials();
    }
    catch(Exceptions)
    {
        LogFailure(Log::mMaterial, error)
    }
    LogSuccess(Log::mMaterial);
}

MaterialManager::~MaterialManager()
{
    LogPowerDown(Log::mMaterial);
}

void MaterialManager::cacheMaterials()
{
    try
    {
        auto files = Toolkit::FileManager::getFiles(materialDirectory, ".json");

        for (auto& filepath : files)
        {
            std::string name = std::filesystem::path(filepath).stem().string();
            loadMaterialData(name, filepath);
        }
    }
    catch(Exceptions)
    {
        Log(Log::Error, Log::mMaterial, error.what())
    }
}

    // Throw
void MaterialManager::loadMaterialData(std::string name, std::string filepath)
{
    auto data = Toolkit::FileManager::loadJson(filepath);
    if (!data.empty())
    {
        Log(Log::Trace, Log::mMaterial, "Caching {} material with shader {} | texture {}", name, data["shaderName"], data["textureName"]);
        loadMaterial(data["name"], data["shaderName"], data["textureName"], data);
    }
}


void MaterialManager::parseUniforms(std::shared_ptr<Material> material, nlohmann::json data)
{
    if (!data.contains("uniforms"))
    {
        Log(Log::Debug, Log::mFile, "uniforms not present in JSON"); 
        return;
    }   

    for (const auto& uniforms : data["uniforms"])
    { 
        Log(Log::Trace, Log::mMaterial, "Setting uniform {}s | {}", uniforms["type"], uniforms["uniforms"].size());
        
        std::string type = uniforms["type"];
        
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
            Log(Log::Trace, Log::mFile, "No uniforms present for {}", type); 
        }
        else
        {
            Log(Log::Error, Log::mFile, "Unknown type in uniform parse: {}", type); 
        }
    } 
}

    // Attempts to return default material if load fails
std::shared_ptr<Material> MaterialManager::loadMaterial(const std::string name, const std::string shaderName, const std::string textureName, nlohmann::json data )
{
    Log(Log::Debug, Log::Material, "Loading material: {}",  name);

    auto iterator = materialRegistry.find(name);
    if (iterator != materialRegistry.end())
    {
        return iterator->second;
    }

    try
    {
        auto shader  = shaderManager->getShader(shaderName);
        auto texture = textureManager->getTexture(textureName);

        auto material = std::make_shared<Material>(shader);
        material->addTexture(texture); 
        parseUniforms(material, data);  

        materialRegistry[name]= material;
        return material;
    }
    catch(Exceptions)
    {
            Log(Log::Error, Log::mMaterial, "Failed to load material {} \n exception: {}", name, error.what());

            if (materialRegistry.find("default") == materialRegistry.end())
            {
                Throw(Error::runtime, "Default material is missing!");
            }
            return materialRegistry["default"];
    }   
}

std::shared_ptr<Material> MaterialManager::getMaterial(const std::string name) const
{
    auto iterator = materialRegistry.find(name);
    if (iterator != materialRegistry.end())
    {
        return iterator->second;
    }

    Log(Log::Warning, Log::mMaterial, "Material {} not found. Falling back to default material");

    auto defaultIterator = materialRegistry.find("default");
    if (defaultIterator == materialRegistry.end()) 
    {
        Throw(Error::runtime, "Default mesh is missing!", name)
    }
    return defaultIterator->second;
}
 
void MaterialManager::removeMaterial(std::string name)
{
    auto iterator = materialRegistry.find(name);
    if (iterator == materialRegistry.end())
    {
        Log(Log::Debug, Log::mMaterial, "Unable to remove material {} (does not exist)", name);
        return;
    }
    materialRegistry.erase(iterator->first);
}

void MaterialManager::clear()
{
    materialRegistry.clear();
    Log(Log::System, Log::mMaterial, "All materials cleared");
}