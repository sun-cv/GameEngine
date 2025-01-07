#pragma once

#include "CoreUtility.h"
#include "CoreRender.h"

#include "Renderer.h"

#include "Testbench.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"


#include "EntityMemoryPool.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "EntityBuilder.h"

namespace Toolkit 
{
class TestInstancedRenderBatch : public Test
{
    private:


        std::shared_ptr<ShaderManager>          shaderManager;
        std::shared_ptr<TextureManager>         textureManager;
        std::shared_ptr<MeshManager>            meshManager;
        std::shared_ptr<MaterialManager>        materialManager;

        std::shared_ptr<ECS::EntityMemoryPool>  entityMemoryPool;
        std::shared_ptr<ECS::EntityManager>     entityManager;
        std::shared_ptr<ECS::ComponentManager>  componentManager;
        std::shared_ptr<ECS::EntityBuilder>     builder;

        std::shared_ptr<Renderer>               renderer;
        std::shared_ptr<RenderSystem>           renderSystem;

        glm::mat4       projection;
        glm::mat4       view;
        float           rotation = 0.0f;

        unsigned int instanceCount = 1000;

        ECS::Entity entity;
        ECS::Entity entity2;

        bool xtoggle;
        bool ytoggle;
        bool xtoggle2;
        bool ytoggle2;
    
    public:
        TestInstancedRenderBatch();
        ~TestInstancedRenderBatch();

        void generateEntity();

        void onUpdate(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;

};
}


