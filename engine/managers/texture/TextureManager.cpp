#include "TextureManager.h"


TextureManager::TextureManager() { initialize(); }

void TextureManager::initialize() {
    std::cout << "[SYSTEM]::[TEXTUREMANAGER] Starting Texture Manager.." << std::endl;
    cacheTextures();
    std::cout << "[SYSTEM]::[TEXTUREMANAGER] Loaded successfully." << std::endl;
}

void TextureManager::cacheTextures() {
    auto files = FileManager::getFiles(textureDirectory, ".png");

    for (const auto& filePath : files) {
        std::string name = std::filesystem::path(filePath).stem().string();
        loadTextureFromFile(name, filePath);
    }
}

std::shared_ptr<Texture> TextureManager::loadTextureFromFile(const std::string& name,
                                                             const std::string& filePath) {
    // Check if texture already exists
    if (textureRegistry.find(name) != textureRegistry.end()) {
        std::cout << "[NOTICE]::[TEXTUREMANAGER] Texture already loaded: " << name << std::endl;
        return textureRegistry[name];
    }

    try {
        auto texture = std::make_shared<Texture>(filePath);
        textureRegistry[name] = texture;
        return texture;
    } catch (const std::exception& e) {
        std::cerr << "[FAILED]::[TEXTUREMANAGER] Failed to load texture '" << name
                  << "' from file: " << filePath << "\n"
                  << "Exception: " << e.what() << std::endl;

        if (textureRegistry.find("default") != textureRegistry.end()) {
            return textureRegistry["default"];
        } else {
            std::cerr << "[BROKEN]::[TEXTUREMANAGER] Default texture is missing!" << std::endl;
            return nullptr;
        }
    }
}

std::shared_ptr<Texture> TextureManager::getTextureByName(const std::string& name) const {
    auto it = textureRegistry.find(name);
    if (it != textureRegistry.end()) {
        return it->second;
    }

    std::cerr << "[NOTICE]::[TEXTUREMANAGER] Texture not found: " << name
              << ". Falling back to default texture." << std::endl;

    auto defaultIt = textureRegistry.find("default");
    if (defaultIt != textureRegistry.end()) {
        return defaultIt->second;
    }

    std::cerr << "[BROKEN]::[TEXTUREMANAGER] Default texture is missing!" << std::endl;
    return nullptr;
}

void TextureManager::removeTexture(const std::string& name) {
    auto it = textureRegistry.find(name);
    if (it != textureRegistry.end()) {
        textureRegistry.erase(it);
        std::cout << "[SYSTEM]::[TEXTUREMANAGER] Removed texture: " << name << std::endl;
    } else {
        std::cerr << "[NOTICE]::[TEXTUREMANAGER] Texture not found: " << name << std::endl;
    }
}

void TextureManager::clear() {
    textureRegistry.clear();
    std::cout << "[SYSTEM]::[TEXTUREMANAGER] All textures cleared." << std::endl;
}
