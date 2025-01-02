#pragma once

#include "CoreUtility.h"
#include "CoreRender.h"

#include "Renderer.h"

#include "Testbench.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"

#include "Entity.h"
#include "EntityManager.h"
#include "EntityBuilder.h"


namespace Toolkit 
{
class TestECSComponents : public Test
{
    private:
        std::shared_ptr<ShaderManager>      shaderManager;
        std::shared_ptr<TextureManager>     textureManager;
        std::shared_ptr<MeshManager>        meshManager;
        std::shared_ptr<MaterialManager>    materialManager;

        std::shared_ptr<ECS::EntityManager> entityManager;
        std::shared_ptr<ECS::EntityBuilder> builder;
        std::optional<ECS::Entity>          entity;

        glm::vec3       translationA;
        glm::vec3       translationB;

        glm::mat4       projection;
        glm::mat4       view;
        float           rotation = 0.0f;

        unsigned int instanceCount = 1000;

        bool xtoggle;
        bool ytoggle;

    public:
        TestECSComponents();
        ~TestECSComponents();

        void generateEntity ();
        void onUpdate       (float deltaTime) override;
        void onRender       () override;
        void onImGuiRender  () override;
};
}


