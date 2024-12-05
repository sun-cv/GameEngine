#include "EngineCore.h"
#include "EntityManager.h"
#include "TransformComponent.h"

class UITransformSystem {
   public:
    void update(EntityManager& entityManager) {
        for (auto& entity : entityManager.getEntitiesWith<UITransformComponent>()) {
            auto& transform = entityManager.getComponent<UITransformComponent>(entity);

            // Example logic: Center a health bar
            if (transform.size != glm::vec2(0)) {
                transform.position = glm::vec2(0.5f) - (transform.size * 0.5f);
            }
        }
    }
};
