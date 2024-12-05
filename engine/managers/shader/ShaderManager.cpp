#include "ShaderManager.h"
ShaderManager::ShaderManager() { initialize(); }

ShaderManager::~ShaderManager() { shaders.clear(); }

void ShaderManager::initialize() {
    std::cout << "[SYSTEM]::[SHADERMANAGER] Starting Shader Manager.." << std::endl;
    preloadShaders(shaderDirectory);
    std::cout << "[SYSTEM]::[SHADERMANAGER] Loaded successfully" << std::endl;
}

std::shared_ptr<Shader> ShaderManager::loadShader(const std::string& name, const std::string& vertexPath,
                                                  const std::string& fragmentPath, GLuint VAO) {
    if (shaders.find(name) != shaders.end()) {
        std::cout << "[NOTICE]::[SHADERMANAGER] Shader exists: " << name << std::endl;
        return shaders[name];
    }

    try {
        auto shader = std::make_shared<Shader>(vertexPath.c_str(), fragmentPath.c_str());

        shaders[name] = shader;

        std::cout << "[SYSTEM]::[SHADERMANAGER] Shader Loaded: " << name << std::endl;
        return shader;

    } catch (const std::exception& e) {
        std::cout << "[FAILED]::[SHADERMANAGER] Load Failed: " << name << "': " << e.what() << "\n";
        return nullptr;
    }
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& name) const {
    auto iterator = shaders.find(name);
    if (iterator != shaders.end()) {
        return iterator->second;
    }

    std::cout << "[NOTICE]::[SHADERMANAGER] Lookup failed: " << name << std::endl;

    auto defaultIterator = shaders.find("default");
    if (defaultIterator != shaders.end()) {
        std::cout << "[NOTICE]::[SHADERMANAGER] Using default shader as fallback" << std::endl;
        return defaultIterator->second;
    } else {
        return nullptr;
    }
}

void ShaderManager::removeShader(const std::string& name) {
    auto iterator = shaders.find(name);
    if (iterator != shaders.end()) {
        shaders.erase(iterator);
    } else {
        std::cout << "[FAILED]::[SHADERMANAGER] Removal failed (shader not found) " << name << std::endl;
    }
}

void ShaderManager::preloadShaders(const std::string& shaderDirectory) {
    auto files = FileManager::getFiles(shaderDirectory, ".json");

    for (const auto& filePath : files) {
        std::string prefabName = std::filesystem::path(filePath).stem().string();

        auto jsonData = FileManager::loadJson(filePath);
        if (!jsonData.empty()) {
            loadShader(jsonData["name"], jsonData["vertexPath"], jsonData["fragmentPath"]);
        }
    }
}
