#include "RenderSystem.h"




RenderSystem::RenderSystem(std::shared_ptr<Renderer> renderer, std::shared_ptr<ECS::EntityManager> entityManager, std::shared_ptr<MeshManager> meshManager, std::shared_ptr<MaterialManager> materialManager) : renderer(renderer), entityManager(entityManager), meshManager(meshManager), materialManager(materialManager)
{
    Log_(Log::System, Log::sRender, "Initializing..")
    
    Log_(Log::System, Log::sRender, "Initialized successfully!")
}

void RenderSystem::update()
{
    sortEntities();
}


void RenderSystem::sortEntities()
{
    layerSort();
    instanceSort();
}

void RenderSystem::layerSort() {
    for (auto& entity : entityManager->getEntities())
    {
        if (entity.has<Render>())
        {
            auto& render    = entity.get<Render>();
            auto& transform = entity.get<Transform>();

            RenderGroup group;
            group.mesh      = meshManager->getMesh(render.mesh);
            group.material  = materialManager->getMaterial(render.material);
            group.transform = &transform;

            layerSortedEntities[render.layer].push_back(group);
        }
    }
}


void RenderSystem::instanceSort()
{
    for ( auto& group : layerSortedEntities)
    {
        auto& layer         = group.first;
        auto& renderGroup   = group.second;

        for (size_t i = 0; i < renderGroup.size(); i++)
        {
            auto& mesh      = renderGroup[i].mesh;
            auto& material  = renderGroup[i].material;
            auto* transform = renderGroup[i].transform;

            instanceLayerSortedEntities[layer][{mesh, material}].push_back(transform);
        }
    }
}




void RenderSystem::setViewProjection()
{
}


void RenderSystem::render()
{
    renderer->clear(clearScreen);  
}
