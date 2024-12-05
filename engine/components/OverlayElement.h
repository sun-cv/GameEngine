#ifndef OVERLAY_ELEMENT_H
#define OVERLAY_ELEMENT_H

#include "EngineCore.h"
#include "HUDComponent.h"
#include "TextComponent.h"

struct BaseComponent {
    virtual ~BaseComponent() = default;
};

struct OverlayElement {
    std::unordered_map<std::type_index, std::vector<std::shared_ptr<BaseComponent>>> components;

    template <typename T>
    void addComponent(std::shared_ptr<T> component) {
        components[typeid(T)].push_back(component);
    }

    template <typename T>
    const std::vector<std::shared_ptr<T>>& getComponents() const {
        auto it = components.find(typeid(T));
        if (it != components.end()) {
            return reinterpret_cast<const std::vector<std::shared_ptr<T>>&>(it->second);
        }
        static const std::vector<std::shared_ptr<T>> empty;
        return empty;
    }
};

#endif