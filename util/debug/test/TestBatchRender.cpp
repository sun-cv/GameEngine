#include "TestBatchRender.h"

#include "RenderGladGLFW.h"

namespace Toolkit
{
BatchRender::BatchRender() : translationA(200, 200, 0), translationB(400, 200, 0)
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float positions     [] =
    {
          0.0f,   0.0f,   0.0f,   0.0f,
        100.0f,   0.0f,   1.0f,   0.0f,
        100.0f, 100.0f,   1.0f,   1.0f,
          0.0f, 100.0f,   0.0f,   1.0f,
        200.0f, 200.0f,   0.0f,   0.0f,
        300.0f, 200.0f,   1.0f,   0.0f,
        300.0f, 300.0f,   1.0f,   1.0f,
        200.0f, 300.0f,   0.0f,   1.0f,
    };
    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4
    };

    projection    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    view          = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    VAO = std::make_unique<VertexArray>();
    VBO = std::make_unique<VertexBuffer>(positions, 4 * 8 * sizeof(float));

    VertexBufferLayout  layout;
    layout.push<float>(2);
    layout.push<float>(2);

    VAO->addVBO(*VBO, layout);
    
    IBO = std::make_unique<IndexBuffer>(indices, 12);
    VAO->addIBO(*IBO);
    
    shader  = shaderManager.getShader("projection");
    texture = textureManager.getTexture("versus");
    texture2 = textureManager.getTexture("default");

    shader->bind();
    shader->setUniform("uColor", { 1.0f, .8f, .8f, 1.0f } );
    shader->setUniform("uTexture", 0);

    VAO->unbind();
    VBO->unbind();
    IBO->unbind();
    shader->unbind();
    texture->unbind();
}

BatchRender::~BatchRender()
{

}


void BatchRender::onUpdate(float deltaTime)
{
}

void BatchRender::onRender()
{

    if (count == 0) counting = 1;
    if (count == 1000) counting = -1;

    if (counting == -1) texture->bind();
    if (counting ==  1) texture2->bind();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 model         = glm::translate(glm::mat4(1.0f), translationA);
    glm::mat4 mvp           = projection * view * model;
    
    shader->bind();
    shader->setUniform("MVP", mvp);

    renderer.draw(*VAO, *shader);

    count += counting;
}

void BatchRender::onImGuiRender()
{
    ImGui::SliderFloat3("float", &translationA.x, 0.0f, 1180.0f);          
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}