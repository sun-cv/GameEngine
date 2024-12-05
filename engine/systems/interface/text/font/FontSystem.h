#ifndef FONT_SYSTEM_H
#define FONT_SYSTEM_H

#include <filesystem>

#include "EngineCore.h"
#include "FileManager.h"
#include "FontAtlas.h"
#include "MaterialManager.h"

class FontSystem {
   public:
    FontSystem(MaterialManager& materialManager);
    void initialize();

    std::shared_ptr<FontAtlas> getFontAtlas(const std::string& name) const;

   private:
    MaterialManager& materialManager;

    std::unordered_map<std::string, std::shared_ptr<FontAtlas>> fontRegistry;

    void loadFontAtlas(const std::string& name, const std::string& filePath);
    std::string fontDirectory = "D:/Projects/GameEngine/assets/textures/fonts";
};

#endif
