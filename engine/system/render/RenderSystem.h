#pragma once

class EntityManager;

#include "CoreUtility.h"
#include "CoreToolkit.h"
#include "CoreMath.h"

#include "ECSDefinition.h"

#include "Renderer.h"
#include "EntityManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"

#include "Entity.h"

struct RenderGroup 
{
    std::shared_ptr<Mesh>       mesh;
    std::shared_ptr<Material>   material;
    Transform*                  transform;
};


class RenderSystem
{
    private:
        std::shared_ptr<Renderer>               renderer;
        std::shared_ptr<ECS::EntityManager>     entityManager;
        std::shared_ptr<MeshManager>            meshManager;
        std::shared_ptr<MaterialManager>        materialManager;

        glm::vec4 clearScreen                   = {0.0f, 0.0f, 0.0f, 1.0f};
        
        glm::mat4 projMatrix                    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::vec4 viewMatrix;

        std::map<
            int,
            std::vector<RenderGroup>>           layerSortedEntities;

        std::map<
            int,
            std::unordered_map<
                std::pair<
                    std::shared_ptr<Mesh>,
                    std::shared_ptr<Material>>,
                std::vector<Transform*>,
                PairHash>>                      instanceLayerSortedEntities;


    private:

        void sortEntities();
        void layerSort();
        void instanceSort();

    public:
        RenderSystem(std::shared_ptr<Renderer> renderer, std::shared_ptr<ECS::EntityManager> entityManager, std::shared_ptr<MeshManager> meshManager, std::shared_ptr<MaterialManager> materialManager);

        void setViewProjection();

        void update();


        void render();

};


    // projection    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    // view          = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
