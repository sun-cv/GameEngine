#pragma once

#include "CoreUtility.h"
#include "Shader.h"


class ShaderManager
{
    private:
        std::string shaderDirectory = "D:/Projects/Active/GameEngine/engine/system/render/shader/shaders";
        std::unordered_map<std::string, std::shared_ptr<Shader>> shaderRegistry;

        void cacheShaders();

    public:
        ShaderManager();

        std::shared_ptr<Shader> loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        std::shared_ptr<Shader> getShader (const std::string& name) const;

        void removeShader(std::string& name);
        void clear();

};

