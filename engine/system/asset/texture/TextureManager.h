#pragma once

#include "CoreUtility.h"
#include "CoreToolkit.h"

#include "Texture.h"

class TextureManager
{
    private:
        std::string textureDirectory = "D:/Projects/Active/GameEngine/assets/texture";
        std::unordered_map<std::string, std::shared_ptr<Texture>> textureRegistry;

        void cacheTextures();

    public:
        TextureManager();

        std::shared_ptr<Texture> loadTexture(const std::string& name, const std::string& filepath);
        std::shared_ptr<Texture> getTexture (const std::string& name) const;    

        void removeTexture(const std::string& name);
        void clear();
};
