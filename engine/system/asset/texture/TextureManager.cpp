#include "TextureManager.h"

#include <nlohmann/json.hpp>

TextureManager::TextureManager()
{
    LogStartup(Log::mTexture);
    try
    {
        cacheTextures();
    }
    catch(Exceptions)
    {
        LogFailure(Log::mTexture, error)
    }
    LogSuccess(Log::mTexture);
}

TextureManager::~TextureManager()
{
    LogPowerDown(Log::mTexture);
}
;


void TextureManager::cacheTextures()
{
    try
    {
        auto files = Toolkit::FileManager::getFiles(textureDirectory, ".png");
        for (const auto& filepath : files)
        {
            std::string name = std::filesystem::path(filepath).stem().string();
            loadTexture(name, filepath);
        }
    }
    catch(Exceptions)
    {
        Log(Log::Error, Log::mTexture, error.what());
    }
}
std::shared_ptr<Texture> TextureManager::loadTexture(const std::string& name, const std::string& filepath)
{
    Log(Log::Debug, Log::Texture, "Loading texture: {}", name);
    auto iterator = textureRegistry.find(name);
    if (iterator != textureRegistry.end())
    {
        return iterator->second;
    }
    
    try
    {
        auto texture = std::make_shared<Texture>(name, filepath);
        textureRegistry[name] = texture;
        return texture;
    }
    catch(Exceptions)
    {
        Log(Log::Error, Log::mTexture, "Failed to load texture {} from file: {} \n exception: {}", name, filepath, error.what());
        if (textureRegistry.find("default") == textureRegistry.end())
        {
            Throw(Error::runtime, "Default texture is missing!");
        }
        return textureRegistry["default"];
    }
}

std::shared_ptr<Texture> TextureManager::getTexture(const std::string& name) const
{
    auto iterator = textureRegistry.find(name);
    if (iterator != textureRegistry.end())
    {
        return iterator->second;
    }
    Log(Log::Warning, Log::mTexture, "Texture {} not found. Falling back to default texture");
    auto defaultIterator = textureRegistry.find("default");
    if (defaultIterator != textureRegistry.end()) 
    {
        Throw(Error::runtime, "Default Texture is missing!");
    }
        return defaultIterator->second;
}    
void TextureManager::removeTexture(const std::string& name)
{
    auto iterator = textureRegistry.find(name);
    if (iterator == textureRegistry.end())
    {
        Log(Log::Warning, Log::mShader, "Cannot remove shader {} (not found)", name);
    }
    
    Log(Log::Debug, Log::mTexture, "Removed texture: {}", name);
    textureRegistry.erase(iterator->first);
}

void TextureManager::clear()
{
    textureRegistry.clear();
    Log(Log::System, Log::mTexture, "All textures cleared");
}
