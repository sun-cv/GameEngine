#include "RenderSystem.h"


RenderSystem::RenderSystem(std::shared_ptr<Renderer> renderer, std::shared_ptr<ECS::EntityManager> entityManager, std::shared_ptr<ECS::ComponentManager> componentManager, std::shared_ptr<MeshManager> meshManager, std::shared_ptr<MaterialManager> materialManager) : renderer(renderer), entityManager(entityManager), componentManager(componentManager), meshManager(meshManager), materialManager(materialManager)
{
    LogSuccess(Log::sRender);
}

RenderSystem::~RenderSystem()
{
    LogPowerDown(Log::sRender);
}

void RenderSystem::setViewProjection()
{
}

void RenderSystem::update()
{   
    try
    {
        sortEntities();
    }
    catch(Exceptions)
    {
        Log(Log::Error, Log::sRender, "Update failed: {}", error.what());
    }
    
}


void RenderSystem::sortEntities()
{
    for (auto& entityID : entityManager->getDirtyEntities())
    {
        auto& render = componentManager->edit<ECS::Render>(entityID);

        if (!render.flag.fresh && !render.flag.depth) continue;

        if (render.flag.depth)
        {
            auto& filter   = sortMap[entityID];
            auto& vector   = instanceSortedEntities[filter.layer][{filter.mesh, filter.material}];
            auto iterator  = std::find(vector.begin(), vector.end(), entityID);

            if (iterator == vector.end())
            {
                Throw(Error::runtime, "Entity instanced map deletion failed | Desync possible");
            }
            vector.erase(iterator);
        }

        instanceSortedEntities[render.layer][{render.mesh, render.material}].push_back(entityID);

        render.flag.depth = false;
        render.flag.fresh = false;
        sortMap[entityID] = {render.mesh, render.material, render.layer};
    }
}


void RenderSystem::instancedRenderPass()
{
    try
    {
        for (auto& layer : instanceSortedEntities)
        {
            for (auto& instanceMap : layer.second )
            {
                std::vector<glm::mat4> instanceBuffer;

                auto& IDPair     = instanceMap.first;
                auto& entities   = instanceMap.second;

                auto& meshID     = IDPair.first;
                auto& materialID = IDPair.second;

                auto mesh        = meshManager->getMesh(meshID);
                auto material    = materialManager->getMaterial(materialID);

                for (auto& entityID : entities)
                {
                    auto& transform = componentManager->get<ECS::Transform>(entityID).modelMatrix;
                    instanceBuffer.push_back(transform);

                }

                mesh->instanceBuffer(instanceBuffer);

                material->setUniform("projection", projectionMatrix);
                material->setUniform("view", viewMatrix);
                renderer->drawInstance(mesh, material, instanceBuffer.size());
            }
        }
    }
    catch(Exceptions)
    {
        Throw(Error::runtime, "Failed RenderPass : {}", error.what())
    }
    
}



void RenderSystem::clear()
{
    renderer->clear(clearScreen);
}

void RenderSystem::render()
{
    instancedRenderPass();
}
