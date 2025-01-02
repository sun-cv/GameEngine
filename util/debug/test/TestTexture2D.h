#pragma once

#include "Coreutility.h"
#include "CoreRender.h"

#include "RendererDep.h"

#include "Testbench.h"
#include "ShaderManager.h"
#include "TextureManager.h"


namespace Toolkit 
{
class TestTexture2D : public Test
{
    private:
        ShaderManager                   shaderManager;
        TextureManager                  textureManager;

        std::unique_ptr<VertexArray>    VAO;
        std::unique_ptr<VertexBuffer>   VBO;
        std::unique_ptr<IndexBuffer>    IBO;

        std::shared_ptr<Shader>         shader;
        std::shared_ptr<Texture>        texture;      

        glm::vec3       translationA;
        glm::vec3       translationB;

        glm::mat4       projection;
        glm::mat4       view;

    public:
        TestTexture2D();
        ~TestTexture2D();

        void onUpdate       (float deltaTime) override;
        void onRender       () override;
        void onImGuiRender  () override;
};
}

