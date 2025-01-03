#include "ShaderManager.h"

#include <nlohmann/json.hpp>
#include "CoreToolkit.h"




ShaderManager::ShaderManager()
{
    Log_(Log::System, Log::mShader, "initializing..");
    cacheShaders();
    Log_(Log::System, Log::mShader, "Initialized successfully!");
}

void ShaderManager::cacheShaders()
{
    try
    {
        auto files = Toolkit::FileManager::getFiles(shaderDirectory, ".json");

        for (auto& filepath : files)
        {
            std::string name = std::filesystem::path(filepath).stem().string();
            loadShaderData(name, filepath);
        }
    }
    catch(Exceptions)
    {
        Log_(Log::Error, Log::mShader, error.what())
    }
}

void ShaderManager::loadShaderData(std::string name, std::string filepath)
{
    try
    {
        auto data = Toolkit::FileManager::loadJson(filepath);
        if (!data.empty())
        {
            loadShader(data["name"], data["vertexPath"], data["fragmentPath"]);
            Log_(Log::Trace, Log::mShader, "Caching {} shader from path: \n         ::[Vertex] {} \n         ::[Fragment] {}", name, data["vertexPath"], data["fragmentPath"]);
        }
    }
    catch(...)
    {
        throw;
    }
}



std::shared_ptr<Shader> ShaderManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
    Log_(Log::Debug, Log::Shader, "Loading shader: {}", name);

    auto iterator = shaderRegistry.find(name);
    if (iterator != shaderRegistry.end())
    {
        return iterator->second;
    }

    try
    {
        auto shader = std::make_shared<Shader>(name, vertexPath, fragmentPath);

        shaderRegistry[name] = shader;
        
        return shader;
    }
    catch(Exceptions)
    {
        Log_(Log::Error, Log::mShader, "Failed to load shader {} from \nVertex: {} \nFragment: {}\n exception: {}", name, vertexPath, fragmentPath, error.what());

        if (shaderRegistry.find("default") != shaderRegistry.end())
        {
            Throw_(Error::runtime, "Default Shader is missing!");
        }
        return shaderRegistry["default"];
    }
}
    

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& name) const
{
    auto iterator = shaderRegistry.find(name);
    if (iterator != shaderRegistry.end())
    {
        return iterator->second;
    }

    Log_(Log::Warning, Log::mShader, "Shader {} not found. Falling back to default shader");

    auto defaultIterator = shaderRegistry.find("default");
    if (defaultIterator == shaderRegistry.end()) 
    {
        Throw_(Error::runtime, "Default Shader is missing!");
    }
    return defaultIterator->second;
}

void ShaderManager::removeShader(std::string& name)
{
    auto iterator = shaderRegistry.find(name);
    if (iterator == shaderRegistry.end())
    {
        Log_(Log::Warning, Log::mShader, "Cannot remove shader {} (not found)", name);
    }

    Log_(Log::Debug, Log::mShader, "Removed shader: {}", name);
    shaderRegistry.erase(iterator);
}

void ShaderManager::clear()
{
    shaderRegistry.clear();
    Log_(Log::System, Log::mShader, "All shaders cleared");
}

