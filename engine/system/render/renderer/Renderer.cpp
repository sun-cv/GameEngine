#include "Renderer.h"

#include "CoreRender.h"

void Renderer::draw(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh) const
{

    material->bind();
    mesh->bind();

    glDrawElements(GL_TRIANGLES, mesh->VAO->getIndexCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::drawInstance( std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, ECS::Entity instanceCount) const
{

    material->bind();
    mesh->bind();

    glDrawElementsInstanced(GL_TRIANGLES, mesh->VAO->getIndexCount(), GL_UNSIGNED_INT, nullptr, static_cast<unsigned int>(instanceCount));

    material->unbind();
    mesh->unbind();
}

void Renderer::clear(glm::vec4 clearColor) const
{
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
