#include "TestMesh.h"


namespace Toolkit
{
TestMesh::TestMesh() : translationA(200, 200, 0), translationB(400, 200, 0)
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    projection    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    view          = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    mesh = meshManager.getMesh("default");
    mesh->bind();
    
    shader  = shaderManager.getShader("projection");
    texture = textureManager.getTexture("versus");

    shader->bind();
    shader->setUniform("uColor", {1.0f, 1.0f, 1.0f, 1.0f});
    shader->setUniform("uTexture", 0);

    mesh->unbind();
    shader->unbind();
    texture->unbind();
}

TestMesh::~TestMesh()
{

}


void TestMesh::onUpdate(float deltaTime)
{
}

void TestMesh::onRender()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    RendererDep renderer;

    texture->bind();

    {
        glm::mat4 model         = glm::translate(glm::mat4(1.0f), translationA);
        glm::mat4 mvp           = projection * view * model;
        shader->bind(); 
        shader->setUniform("MVP", mvp);
        renderer.draw(*mesh->VAO, *shader);
    }
    {
        glm::mat4 model         = glm::translate(glm::mat4(1.0f), translationB);
        glm::mat4 mvp           = projection * view * model;
        shader->bind(); 
        shader->setUniform("MVP", mvp);
        renderer.draw(*mesh->VAO, *shader);
    }
}

void TestMesh::onImGuiRender()
{
    ImGui::SliderFloat3("float1", &translationA.x, 0.0f, 1180.0f);          
    ImGui::SliderFloat3("float", &translationB.x, 0.0f, 1180.0f);          
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}