#pragma once

#include "Coreutility.h"
#include "CoreRender.h"

#include "Renderer.h"

#include "Testbench.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"


namespace Toolkit 
{
class TestMeshMaterial : public Test
{
    private:
        std::shared_ptr<ShaderManager>  shaderManager;
        std::shared_ptr<TextureManager> textureManager;
        std::shared_ptr<MeshManager>    meshManager;
        std::shared_ptr<MaterialManager>materialManager;

        std::shared_ptr<Mesh>           mesh;
        std::shared_ptr<Material>       material;

        std::shared_ptr<Mesh>           mesh1;
        std::shared_ptr<Material>       material1;

        glm::vec3       translationA;
        glm::vec3       translationB;

        glm::mat4       projection;
        glm::mat4       view;

    public:
        TestMeshMaterial();
        ~TestMeshMaterial();

        void onUpdate       (float deltaTime) override;
        void onRender       () override;
        void onImGuiRender  () override;
};
}

