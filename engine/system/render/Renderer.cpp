#include "Renderer.h"



void Renderer::draw(VertexArray& VAO, Shader& shader) const
{

    shader.bind();
    VAO.bind();

    glDrawElements(GL_TRIANGLES, VAO.getIndexCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::clear() const
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
