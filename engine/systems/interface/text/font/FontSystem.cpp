#include "FontSystem.h"

FontSystem::FontSystem(MaterialManager& materialManager) : materialManager(materialManager) { initialize(); }

void FontSystem::initialize() {
    auto files = FileManager::getFiles(fontDirectory, ".json");
    for (const auto& filePath : files) {
        std::string fileName = std::filesystem::path(filePath).stem().string();
        loadFontAtlas(fileName, filePath);
    }
}

void FontSystem::loadFontAtlas(const std::string& fileName, const std::string& filePath) {
    auto jsonData = FileManager::loadJson(filePath);
    if (!jsonData.contains("name") || !jsonData.contains("fontTexture") || !jsonData.contains("fontWidth") ||
        !jsonData.contains("fontHeight") || !jsonData.contains("atlasRows") || !jsonData.contains("atlasColumns")) {
        std::cerr << "[FAILED]::[FONTSYSTEM] Invalid font metadata in: " << filePath << std::endl;
        return;
    }

    std::string name = jsonData["name"];

    if (fontRegistry.find(name) != fontRegistry.end()) {
        std::cerr << "[NOTICE]::[FONTSYSTEM] Font already loaded: " << name << std::endl;
        return;
    }

    auto material = materialManager.createMaterial(name, jsonData["fontShader"], jsonData["fontTexture"]);
    auto fontAtlas =
        std::make_shared<FontAtlas>(jsonData["name"], material, jsonData["fontWidth"], jsonData["fontHeight"],
                                    jsonData["atlasRows"], jsonData["atlasColumns"]);

    fontRegistry[name] = fontAtlas;
    std::cout << "[SYSTEM]::[FONTSYSTEM] Successfully generated Font: " << name << std::endl;
}

std::shared_ptr<FontAtlas> FontSystem::getFontAtlas(const std::string& name) const {
    auto it = fontRegistry.find(name);
    if (it != fontRegistry.end()) return it->second;
    std::cerr << "[NOTICE]::[FONTSYSTEM] Font not found: " << name << std::endl;
    return nullptr;
}
