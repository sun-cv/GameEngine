#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "EngineCore.h"
#include "FileManager.h"
#include "Texture.h"

class TextureManager {
   public:
    TextureManager();

    void initialize();

    std::shared_ptr<Texture> loadTextureFromFile(const std::string& name, const std::string& filePath);
    std::shared_ptr<Texture> getTextureByName(const std::string& name) const;

    void removeTexture(const std::string& name);
    void clear();

   private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> textureRegistry;
    std::string textureDirectory = "D:/Projects/GameEngine/assets/textures";

    void cacheTextures();
};

#endif
