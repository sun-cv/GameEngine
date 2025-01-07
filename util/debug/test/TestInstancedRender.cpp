#include "TestInstancedRender.h"


namespace Toolkit
{
TestInstancedRender::TestInstancedRender()
{


    meshManager     = std::make_shared<MeshManager>();
    shaderManager   = std::make_shared<ShaderManager>();
    textureManager  = std::make_shared<TextureManager>();
    materialManager = std::make_shared<MaterialManager>(shaderManager, textureManager);

    entityMemoryPool= std::make_shared<ECS::EntityMemoryPool>();
    entityManager   = std::make_shared<ECS::EntityManager>(entityMemoryPool);
    componentManager= std::make_shared<ECS::ComponentManager>(entityMemoryPool);
    builder         = std::make_shared<ECS::EntityBuilder>(entityManager, componentManager);

    renderer        = std::make_shared<Renderer>();
    renderSystem    = std::make_shared<RenderSystem>(renderer, entityManager, componentManager, meshManager, materialManager);
    
    view            = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    generateEntity();
}

TestInstancedRender::~TestInstancedRender()
{

}


void TestInstancedRender::generateEntity()
{
    
    entity = builder->create()
        .player(true)
        .lifespan(100)
        .position({0,0})
        .velocity({0.1f,0.1f})
        .transform()
        .render("large_default", "instance_default", 1)
        .complete();


    entity2 = builder->create()
        .player(true)
        .lifespan(100)
        .position({0, 0})
        .velocity({0.1f,0.1f})
        .render("default", "instance_default", 0)
        .complete();
}

void TestInstancedRender::onUpdate(float deltaTime)
{
    renderSystem->update();
}

void logMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void TestInstancedRender::onRender()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    {
        rotation += glm::radians(0.1f);

        auto& position   = componentManager->edit<ECS::Position>(entity);
        auto& position2  = componentManager->edit<ECS::Position>(entity2);

        auto& velocity   = componentManager->edit<ECS::Velocity>(entity);
        auto& velocity2  = componentManager->edit<ECS::Velocity>(entity2);

        auto& transform  = componentManager->edit<ECS::Transform>(entity);
        auto& transform2 = componentManager->edit<ECS::Transform>(entity2);

        auto mesh  = meshManager->getMesh(componentManager->get<ECS::Render>(entity).mesh);
        auto mesh2 = meshManager->getMesh(componentManager->get<ECS::Render>(entity2).mesh);


        if (xtoggle)   position.x  += velocity.x;
        if (!xtoggle)  position.x  -= velocity.x;
        if (ytoggle)   position.y  += velocity.y;
        if (!ytoggle)  position.y  -= velocity.y;

        if (xtoggle2)  position2.x  += velocity2.x;
        if (!xtoggle2) position2.x  -= velocity2.x;
        if (ytoggle2)  position2.y  += velocity2.y;
        if (!ytoggle2) position2.y  -= velocity2.y;

        if (position.x > 1280 - mesh->width) xtoggle = false;
        if (position.x < 0) xtoggle = true;
        if (position.y > 720 - mesh->height) ytoggle = false;
        if (position.y < 0) ytoggle = true;

        if (position2.x > 1280 - mesh2->width) xtoggle2 = false;
        if (position2.x < 0) xtoggle2 = true;
        if (position2.y > 720 - mesh2->height) ytoggle2 = false;
        if (position2.y < 0) ytoggle2 = true;
        
        transform.reset();
        transform2.reset();

        transform.modelMatrix = glm::translate(transform.modelMatrix, glm::vec3(position.x + mesh->width / 2, position.y + mesh->height / 2, 0));
        transform2.modelMatrix = glm::translate(transform2.modelMatrix, glm::vec3(position2.x + mesh2->width / 2, position2.y + mesh2->height / 2, 0));

        renderSystem->render();
    }
}


void TestInstancedRender::onImGuiRender()
{
    ImGui::PushItemWidth(150.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}