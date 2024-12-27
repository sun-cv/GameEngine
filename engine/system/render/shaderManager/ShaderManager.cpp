#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
    Log_(Log::System, Log::mShader, "initializing..");
    cacheShaders();
    Log_(Log::System, Log::mShader, "Initialized successfully!");
}

void ShaderManager::cacheShaders()
{
    auto files = Toolkit::FileManager::getFiles(shaderDirectory, ".json");

    for (auto& filepath : files)
    {
        std::string name = std::filesystem::path(filepath).stem().string();

        auto data = Toolkit::FileManager::loadJson(filepath);
        if (!data.empty())
        {
            loadShader(data["name"], data["vertexPath"], data["fragmentPath"]);
            Log_(Log::Trace, Log::mShader, "Caching {} shader from path: \n         ::[Vertex] {} \n         ::[Fragment] {}", name, data["vertexPath"], data["fragmentPath"]);
        }
    }
}

std::shared_ptr<Shader> ShaderManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
    if (shaderRegistry.find(name) != shaderRegistry.end())
    {
        Log_(Log::Warning, Log::mShader, "Shader {} already loaded", name);
        return shaderRegistry[name];
    }
    try
    {
        auto shader = std::make_shared<Shader>(name, vertexPath, fragmentPath);
        shaderRegistry[name] = shader;
        return shader;
    }
    catch(const std::exception& error)
    {
        Log_(Log::Error, Log::mShader, "Failed to load shader {} from \nVertex: {} \nFragment: {}\n exception: {}", name, vertexPath, fragmentPath, error.what());

        if (shaderRegistry.find("default") != shaderRegistry.end())
        {
            return shaderRegistry["default"];
        }
        else
        {
            Log_(Log::Fatal, Log::mShader, "Default shader is missing!");
            return nullptr;
        }
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
    if (defaultIterator != shaderRegistry.end()) 
    {
        return defaultIterator->second;
    }

    Log_(Log::Fatal, Log::mShader, "Default shader is missing!");
    return nullptr;
}

void ShaderManager::removeShader(std::string& name)
{
    auto iterator = shaderRegistry.find(name);
    if (iterator != shaderRegistry.end())
    {
        shaderRegistry.erase(iterator);
        Log_(Log::Debug, Log::mShader, "Removed shader: {}", name);
    }
    else
    {
        Log_(Log::Warning, Log::mShader, "Shader not found: {}", name);
    }
}

void ShaderManager::clear()
{
    shaderRegistry.clear();
    Log_(Log::System, Log::mShader, "All shaders cleared");
}

