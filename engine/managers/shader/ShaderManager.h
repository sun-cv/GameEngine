#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>


#include "EngineCore.h"
#include "FileManager.h"
#include "Shader.h"

class ShaderManager {
   public:
    ShaderManager();
    ~ShaderManager();
    void initialize();
    void preloadShaders(const std::string& shaderDirectory);

    std::shared_ptr<Shader> loadShader(const std::string& name, const std::string& vertexPath,
                                       const std::string& fragmentPath, GLuint VAO = 0);

    std::shared_ptr<Shader> getShader(const std::string& name) const;

    void removeShader(const std::string& name);

   private:
    std::string shaderDirectory = "D:/Projects/GameEngine/assets/shaders";
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};

#endif  // SHADER_MANAGER_H
