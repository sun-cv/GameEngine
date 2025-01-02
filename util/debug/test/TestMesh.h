#pragma once

#include "CoreUtility.h"
#include "CoreRender.h"

#include "RendererDep.h"

#include "Testbench.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MeshManager.h"

namespace Toolkit 
{
class TestMesh : public Test
{
    private:
        ShaderManager                   shaderManager;
        TextureManager                  textureManager;
        MeshManager                     meshManager;

        std::shared_ptr<Mesh>           mesh;

        std::shared_ptr<Shader>         shader;
        std::shared_ptr<Texture>        texture;      

        glm::vec3       translationA;
        glm::vec3       translationB;

        glm::mat4       projection;
        glm::mat4       view;

    public:
        TestMesh();
        ~TestMesh();

        void onUpdate       (float deltaTime) override;
        void onRender       () override;
        void onImGuiRender  () override;
};
}
