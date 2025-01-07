#pragma once

class EntityManager;

#include "CoreUtility.h"
#include "CoreToolkit.h"
#include "CoreMath.h"

#include "ECSDefinition.h"

#include "Renderer.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "MeshManager.h"
#include "MaterialManager.h"


struct RenderFilter 
{
    std::string  mesh;
    std::string  material;
    unsigned int layer;
};

// REWORK REQUIRED - instanceSortedEntites std::vector<ECS::Entity> Hold vector of transforms?
// MVP view projection pushed from mesh?

class RenderSystem
{   // Variables
    private: // Dependencies
        std::shared_ptr<Renderer>               renderer;
        std::shared_ptr<ECS::EntityManager>     entityManager;
        std::shared_ptr<ECS::ComponentManager>  componentManager;
        std::shared_ptr<MeshManager>            meshManager;
        std::shared_ptr<MaterialManager>        materialManager;

        std::unordered_map<
            ECS::Entity,
            RenderFilter>                       sortMap;
                
        std::map<
            int,
            std::unordered_map<
                std::pair<
                    std::string,
                    std::string
                >,
                std::vector<ECS::Entity>,
                PairHash>>                      instanceSortedEntities;

        glm::vec4 clearScreen                   = {0.0f, 0.0f, 0.0f, 1.0f};
        
        glm::mat4 projectionMatrix                    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::mat4 viewMatrix                          = glm::mat4(1.0f);

    // Functions
    private:
            // Sorting
        void sortEntities();

            // Rendering passes
        void instancedRenderPass();

    public: // Engine
        void clear();
        void update();
        
        void setViewProjection();

        void render();

    public:
        RenderSystem(
            std::shared_ptr<Renderer> renderer,
            std::shared_ptr<ECS::EntityManager> entityManager,
            std::shared_ptr<ECS::ComponentManager> componentManager,
            std::shared_ptr<MeshManager> meshManager,
            std::shared_ptr<MaterialManager> materialManager);
       ~RenderSystem();
};


    // projection    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    // view          = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
