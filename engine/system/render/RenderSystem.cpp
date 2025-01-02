#include "RenderSystem.h"



RenderSystem::RenderSystem(std::shared_ptr<Renderer> renderer, std::shared_ptr<ECS::EntityManager> entityManager) : renderer(renderer), entityManager(entityManager)
{
}

void RenderSystem::setViewProjection()
{
}

void RenderSystem::update()
{
}

void RenderSystem::render()
{
    renderer->clear(clearScreen);  
}
