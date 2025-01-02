#include "TestTexture2D.h"

namespace Toolkit
{
TestTexture2D::TestTexture2D() : translationA(200, 200, 0), translationB(400, 200, 0)
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float positions     [] =
    {
          0.0f,   0.0f,   0.0f,   0.0f,
        100.0f,   0.0f,   1.0f,   0.0f,
        100.0f, 100.0f,   1.0f,   1.0f,
          0.0f, 100.0f,   0.0f,   1.0f
    };

int test = sizeof(positions) / sizeof(positions[0]);

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    projection    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    view          = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    VAO = std::make_unique<VertexArray>();
    VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout  layout;
    layout.push<float>(2);
    layout.push<float>(2);

    VAO->addVBO(*VBO, layout);
    
    IBO = std::make_unique<IndexBuffer>(indices, 6);
    VAO->addIBO(*IBO);
    
    shader  = shaderManager.getShader("projection");
    texture = textureManager.getTexture("versus");

    shader->bind();
    shader->setUniform("uColor", { 1.0f, 1.0f, 1.0f, 1.0f } );
    shader->setUniform("uTexture", 0);

    VAO->unbind();
    VBO->unbind();
    IBO->unbind();
    shader->unbind();
    texture->unbind();
}

TestTexture2D::~TestTexture2D()
{

}


void TestTexture2D::onUpdate(float deltaTime)
{
}

void TestTexture2D::onRender()
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
        renderer.draw(*VAO, *shader);
    }
    {
        glm::mat4 model         = glm::translate(glm::mat4(1.0f), translationB);
        glm::mat4 mvp           = projection * view * model;
        shader->bind(); 
        shader->setUniform("MVP", mvp);
        renderer.draw(*VAO, *shader);
    }
}

void TestTexture2D::onImGuiRender()
{
    ImGui::SliderFloat3("float1", &translationA.x, 0.0f, 1180.0f);          
    ImGui::SliderFloat3("float", &translationB.x, 0.0f, 1180.0f);          
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}