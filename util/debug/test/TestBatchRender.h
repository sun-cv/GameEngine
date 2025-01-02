#pragma once

#include "CoreUtility.h"
#include "CoreRender.h"

#include "RendererDep.h"

#include "Testbench.h"
#include "ShaderManager.h"
#include "TextureManager.h"


namespace Toolkit 
{
class BatchRender : public Test
{
    private:
        ShaderManager                   shaderManager;
        TextureManager                  textureManager;
        RendererDep                        renderer;

        unsigned int                    count = 0;
        unsigned int                    counting = 0;

        std::unique_ptr<VertexArray>    VAO;
        std::unique_ptr<VertexBuffer>   VBO;
        std::unique_ptr<IndexBuffer>    IBO;

        std::shared_ptr<Shader>         shader;
        std::shared_ptr<Texture>        texture;
        std::shared_ptr<Texture>        texture2;      
      

        glm::vec3       translationA;
        glm::vec3       translationB;

        glm::mat4       projection;
        glm::mat4       view;

    public:
        BatchRender();
        ~BatchRender();

        void onUpdate       (float deltaTime) override;
        void onRender       () override;
        void onImGuiRender  () override;
};
}
