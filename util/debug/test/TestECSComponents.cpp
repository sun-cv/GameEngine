#include "TestECSComponents.h"

#include "CoreComponent.h"
#include "RenderGladGLFW.h"

#include "CoreUtility.h"


namespace Toolkit
{
TestECSComponents::TestECSComponents() : translationA(0, 0, 0), translationB(0, 0, 0)
{

    // meshManager     = std::make_shared<MeshManager>();
    // shaderManager   = std::make_shared<ShaderManager>();
    // textureManager  = std::make_shared<TextureManager>();
    // materialManager = std::make_shared<MaterialManager>(shaderManager, textureManager);

    // entityManager   = std::make_shared<ECS::EntityManager>();
    // builder         = std::make_shared<ECS::EntityBuilder>(entityManager, meshManager, materialManager);

    // projection      = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    // view            = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    generateEntity();
}

TestECSComponents::~TestECSComponents()
{

}


void TestECSComponents::generateEntity()
{
    
    // entity = builder->create("test")
    //     .player(true)
    //     .lifespan(100)
    //     .position({0,0})
    //     .velocity({0.1f,0.1f})
    //     .render("large_default", "instance_default")
    //     .complete();

        // auto& render = entity->get<Render>();
        // std::shared_ptr<Mesh> mesh = meshManager->getMesh(render.material);
        // auto& vertices = mesh->getVertices();

    std::vector<glm::mat4> instanceTransforms(2);
    instanceTransforms[0] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    instanceTransforms[1] = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f));
   
//    mesh->instanceBuffer(instanceTransforms);
}

void TestECSComponents::onUpdate(float deltaTime)
{
}

void TestECSComponents::onRender()
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Renderer renderer;

    {

        // rotation += glm::radians(0.1f);

        // auto& render   = entity->get<Render>();
        // auto& position = entity->get<Position>();
        // auto& velocity = entity->get<Velocity>();

        // if (xtoggle) position.x += velocity.x;
        // if (!xtoggle) position.x -= velocity.x;

        // if (ytoggle) position.y += velocity.y;
        // if (!ytoggle) position.y -= velocity.y;

        // if (position.x > 1280 - mesh->width) xtoggle = false;
        // if (position.x < 0) xtoggle = true;
 
        // if (position.y > 720 - mesh->height) ytoggle = false;
        // if (position.y < 0) ytoggle = true;

        // glm::mat4 model         = glm::translate(glm::mat4(1.0f),{position.x + render.mesh->width / 2, position.y + render.mesh->height / 2, 0 });
        // model                   = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        // glm::mat4 mvp           = projection * view * model;
        // render.material->setUniform("MVP", mvp);
        // renderer.drawInstance(render.material, render.mesh, instanceCount);
    }

}

void TestECSComponents::onImGuiRender()
{
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderFloat("A.X", &translationA.x, 0.0f, 1180.0f);
    ImGui::SameLine();
    ImGui::SliderFloat("A.Y", &translationA.y, 0.0f, 620.0f);
    ImGui::PopItemWidth();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}