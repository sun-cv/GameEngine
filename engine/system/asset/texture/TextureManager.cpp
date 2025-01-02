#include "TextureManager.h"

    TextureManager::TextureManager()
    {
        Log_(Log::System, Log::mTexture, "initializing..");
        cacheTextures();
        Log_(Log::System, Log::mTexture, "Initialized successfully!");
    };


    void TextureManager::cacheTextures()
    {
        auto files = Toolkit::FileManager::getFiles(textureDirectory, ".png");

        for (const auto& filepath : files)
        {
            std::string name = std::filesystem::path(filepath).stem().string();
            loadTexture(name, filepath);
        }
    }


    std::shared_ptr<Texture> TextureManager::loadTexture(const std::string& name, const std::string& filepath)
    {
        if (textureRegistry.find(name) != textureRegistry.end())
        {
            Log_(Log::Debug, Log::mTexture, "Texture {} already loaded", name);
            return textureRegistry[name];
        }

        try
        {
            auto texture = std::make_shared<Texture>(name, filepath);
            textureRegistry[name] = texture;
            return texture;
        }
        catch(const std::exception& error)
        {
            Log_(Log::Error, Log::mTexture, "Failed to load texture {} from file: {} \n exception: {}", name, filepath, error.what());

            if (textureRegistry.find("default") != textureRegistry.end())
            {
                return textureRegistry["default"];
            }
            else
            {
                Log_(Log::Fatal, Log::mTexture, "Default texture is missing!");
                return nullptr;
            }
        }
    }
    
    std::shared_ptr<Texture> TextureManager::getTexture(const std::string& name) const
    {
        auto iterator = textureRegistry.find(name);
        if (iterator != textureRegistry.end())
        {
            return iterator->second;
        }

        Log_(Log::Warning, Log::mTexture, "Texture {} not found. Falling back to default texture");

        auto defaultIterator = textureRegistry.find("default");
        if (defaultIterator != textureRegistry.end()) 
        {
            return defaultIterator->second;
        }

        Log_(Log::Fatal, Log::mTexture, "Default texture is missing!");
        return nullptr;
    }    

    void TextureManager::removeTexture(const std::string& name)
    {
        auto iterator = textureRegistry.find(name);
        if (iterator != textureRegistry.end())
        {
            textureRegistry.erase(iterator);
            Log_(Log::Debug, Log::mTexture, "Removed texture: {}", name);
        }
        else
        {
            Log_(Log::Warning, Log::mTexture, "Texture not found: {}", name);
        }
    }
    void TextureManager::clear()
    {
        textureRegistry.clear();
        Log_(Log::System, Log::mTexture, "All textures cleared");
    }
