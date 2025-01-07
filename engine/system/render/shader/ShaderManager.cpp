#include "ShaderManager.h"

#include <nlohmann/json.hpp>
#include "CoreToolkit.h"




ShaderManager::ShaderManager()
{
    LogStartup(Log::mShader);
    try
    {
        cacheShaders();
    }
    catch(Exceptions)
    {
        LogFailure(Log::mShader, error)
    }
    LogSuccess(Log::mShader);
}

ShaderManager::~ShaderManager()
{
    LogPowerDown(Log::mShader);
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
        Log(Log::Error, Log::mShader, error.what())
    }
}

    // Throw
void ShaderManager::loadShaderData(std::string name, std::string filepath)
{
    auto data = Toolkit::FileManager::loadJson(filepath);
    if (!data.empty())
    {
        loadShader(data["name"], data["vertexPath"], data["fragmentPath"]);
        Log(Log::Trace, Log::mShader, "Caching {} shader from path: \n         ::[Vertex] {} \n         ::[Fragment] {}", name, data["vertexPath"], data["fragmentPath"]);
    }
}


std::shared_ptr<Shader> ShaderManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
    Log(Log::Debug, Log::Shader, "Loading shader: {}", name);

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
        Log(Log::Error, Log::mShader, "Failed to load shader {} from \nVertex: {} \nFragment: {}\n exception: {}", name, vertexPath, fragmentPath, error.what());

        if (shaderRegistry.find("default") != shaderRegistry.end())
        {
            Throw(Error::runtime, "Default Shader is missing!");
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

    Log(Log::Warning, Log::mShader, "Shader {} not found. Falling back to default shader");

    auto defaultIterator = shaderRegistry.find("default");
    if (defaultIterator == shaderRegistry.end()) 
    {
        Throw(Error::runtime, "Default Shader is missing!");
    }
    return defaultIterator->second;
}

void ShaderManager::removeShader(std::string& name)
{
    auto iterator = shaderRegistry.find(name);
    if (iterator == shaderRegistry.end())
    {
        Log(Log::Warning, Log::mShader, "Cannot remove shader {} (not found)", name);
    }

    Log(Log::Debug, Log::mShader, "Removed shader: {}", name);
    shaderRegistry.erase(iterator);
}

void ShaderManager::clear()
{
    shaderRegistry.clear();
    Log(Log::System, Log::mShader, "All shaders cleared");
}

