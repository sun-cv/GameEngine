#pragma once

#include "CoreUtility.h"
#include "Shader.h"


class ShaderManager
{   // Variables
    private:
        std::string shaderDirectory             = "D:/Projects/Active/GameEngine/engine/system/render/shader/shaders";

        std::unordered_map<
            std::string,
            std::shared_ptr<Shader>
        >                                       shaderRegistry;

    // Functions
    private: // Initialization
        void cacheShaders();
        void loadShaderData(std::string name, std::string filepath);

    public:
            // Access
        std::shared_ptr<Shader> loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        std::shared_ptr<Shader> getShader (const std::string& name) const;
            // Release
        void removeShader(std::string& name);
        void clear();

    public:
        ShaderManager();
       ~ShaderManager();
};

