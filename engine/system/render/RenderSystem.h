#pragma once

class EntityManager;

#include "CoreUtility.h"
#include "CoreMath.h"

#include "Renderer.h"
#include "EntityManager.h"

class RenderSystem
{
    private:
        std::shared_ptr<Renderer>               renderer;
        std::shared_ptr<ECS::EntityManager>     entityManager;

        glm::vec4 clearScreen                   = {0.0f, 0.0f, 0.0f, 1.0f};
        
        glm::mat4 projMatrix                    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::vec4 viewMatrix;

    public:
        RenderSystem(std::shared_ptr<Renderer> renderer, std::shared_ptr<ECS::EntityManager> entityManager);

        void setViewProjection();

        void update();


        void render();

};


    // projection    = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    // view          = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
