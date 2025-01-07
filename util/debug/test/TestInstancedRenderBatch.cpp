#include "TestInstancedRenderBatch.h"

#include <iostream>
#include <cstdlib> 
#include <ctime>

#include <iostream>
#include <random>
#include <chrono>

namespace Toolkit
{
TestInstancedRenderBatch::TestInstancedRenderBatch()
{


    meshManager         = std::make_shared<MeshManager>();
    shaderManager       = std::make_shared<ShaderManager>();
    textureManager      = std::make_shared<TextureManager>();
    materialManager     = std::make_shared<MaterialManager>(shaderManager, textureManager);
    
    entityMemoryPool    = std::make_shared<ECS::EntityMemoryPool>();
    entityManager       = std::make_shared<ECS::EntityManager>(entityMemoryPool);
    componentManager    = std::make_shared<ECS::ComponentManager>(entityMemoryPool);
    builder             = std::make_shared<ECS::EntityBuilder>(entityManager, componentManager);
    
    renderer            = std::make_shared<Renderer>();
    renderSystem        = std::make_shared<RenderSystem>(renderer, entityManager, componentManager, meshManager, materialManager);
        
    view                = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    generateEntity();
}

TestInstancedRenderBatch::~TestInstancedRenderBatch()
{

}


float random(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_real_distribution<float> dis(min, max);
    
    return dis(gen);
}


void TestInstancedRenderBatch::generateEntity()
{
    for (size_t i = 0; i < 1000; i++)
    {
    
    entity = builder->create()
        .player(true)
        .lifespan(100)
        .position({random(100, 1180), random(100,620)})
        .velocity({random(1, 2), random(1, 5)})
        .transform()
        .render("default", "instance_default", 1)
        .complete();
    

    // entity2 = builder->create()
    //     .player(true)
    //     .lifespan(100)
    //     .position({random(100, 1180), random(100,620)})
    //     .velocity({random(1, 10), random(1, 10)})
    //     .transform()
    //     .render("large_default", "instance_default", 0)
    //     .complete();
    }
}

void TestInstancedRenderBatch::onUpdate(float deltaTime)
{
    renderSystem->update();
}

void TestInstancedRenderBatch::onRender()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    {
        for (auto& entity : entityManager->getEntities())
        {
   
            auto& position   = componentManager->edit<ECS::Position>(entity);
            auto& velocity   = componentManager->edit<ECS::Velocity>(entity);
            auto& transform  = componentManager->edit<ECS::Transform>(entity);

            auto mesh  = meshManager->getMesh(componentManager->get<ECS::Render>(entity).mesh);


            position.x  += velocity.x;
            position.y  += velocity.y;



            if (position.x > 1280 - mesh->width || position.x < 0)    velocity.x = velocity.x * -1;
            if (position.y > 720 - mesh->height || position.y < 0)    velocity.y = velocity.y * -1;

            transform.reset();

            transform.modelMatrix = glm::translate(transform.modelMatrix, glm::vec3(position.x + mesh->width / 2, position.y + mesh->height / 2, 0));
        }
        renderSystem->render();
    }
}


void TestInstancedRenderBatch::onImGuiRender()
{
    ImGui::PushItemWidth(150.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}