#ifndef COMPONENT_REGISTRY_H
#define COMPONENT_REGISTRY_H

#include <cstddef>
#include <typeindex>
#include "EngineCore.h"

#include "Entity.h"
#include "MaterialComponent.h"
#include "RenderableComponent.h"
#include "TransformComponent.h"

class ComponentRegistry {
   public:
    ComponentRegistry(const ComponentRegistry&) = delete;
    ComponentRegistry& operator=(const ComponentRegistry&) = delete;

    static ComponentRegistry& getInstance() {
        static ComponentRegistry instance;
        return instance;
    }

    template <typename ComponentType>
    void registerComponent() {
        std::type_index type = std::type_index(typeid(ComponentType));
        if (componentMaskMapping.find(type) == componentMaskMapping.end()) {
            componentMaskMapping[type] = static_cast<Entity::ComponentMask>(1) << nextMaskBit++;
        }
    }

    template <typename ComponentType>
    Entity::ComponentMask getComponentMask() const {
        std::type_index type = std::type_index(typeid(ComponentType));
        auto iterator = componentMaskMapping.find(type);
        if (iterator == componentMaskMapping.end()) {
            std::cout << "[WARNING] Component type not registered " << type.name() << std::endl;

            return 0;
        }
        return iterator->second;
    }

    template <typename... ComponentTypes>
    Entity::ComponentMask getCombinedMask() const {
        Entity::ComponentMask combinedMask = 0;
        (..., (combinedMask |= getComponentMask<ComponentTypes>()));
        return combinedMask;
    }

   private:
    ComponentRegistry() {
        registerComponent<RenderableComponent>();
        registerComponent<MaterialComponent>();
        registerComponent<TransformComponent>();
    }
    ~ComponentRegistry() = default;

    std::unordered_map<std::type_index, Entity::ComponentMask> componentMaskMapping;
    size_t nextMaskBit = 0;
};

#endif
