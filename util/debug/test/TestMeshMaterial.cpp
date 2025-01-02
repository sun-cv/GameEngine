#include "TestMeshMaterial.h"

namespace Toolkit
{
TestMeshMaterial::TestMeshMaterial() : translationA(200, 200, 0), translationB(400, 200, 0)
{

    shaderManager   = std::make_shared<ShaderManager>();
    textureManager  = std::make_shared<TextureManager>();
    meshManager     = std::make_shared<MeshManager>();
    materialManager = std::make_shared<MaterialManager>(shaderManager, textureManager);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    projection    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    view          = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));




    mesh = meshManager->getMesh("default");
    mesh->bind();

    material = materialManager->getMaterial("default");
    material->bind();


    mesh1 = meshManager->getMesh("default");
    mesh1->bind();

    material1 = materialManager->getMaterial("default");
    material->bind();


    mesh->unbind();
    material->unbind();

}

TestMeshMaterial::~TestMeshMaterial()
{

}


void TestMeshMaterial::onUpdate(float deltaTime)
{
}

void TestMeshMaterial::onRender()
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Renderer renderer;



    {
        glm::mat4 model         = glm::translate(glm::mat4(1.0f), translationA);
        glm::mat4 mvp           = projection * view * model;
        material->setUniform("MVP", mvp);
        renderer.draw(material, mesh);
    }
    {
        glm::mat4 model         = glm::translate(glm::mat4(1.0f), translationB);
        glm::mat4 mvp           = projection * view * model;
        material1->setUniform("MVP", mvp);
        renderer.draw(material, mesh);
    }
}

void TestMeshMaterial::onImGuiRender()
{
    ImGui::PushItemWidth(150.0f);
    ImGui::SliderFloat("A.X", &translationA.x, 0.0f, 1180.0f);
    ImGui::SameLine();
    ImGui::SliderFloat("A.Y", &translationA.y, 0.0f, 620.0f);
    ImGui::Separator();
    ImGui::SliderFloat("B.X", &translationB.x, 0.0f, 1180.0f);
    ImGui::SameLine();
    ImGui::SliderFloat("B.Y", &translationB.y, 0.0f, 620.0f);   
    ImGui::PopItemWidth();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}