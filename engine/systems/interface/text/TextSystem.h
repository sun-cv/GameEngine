#ifndef TEXT_SYSTEM_H
#define TEXT_SYSTEM_H

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "FontAtlas.h"
#include "FontSystem.h"
#include "MaterialManager.h"
#include "TextComponent.h"

class TextSystem {
   public:
    TextSystem(MaterialManager& materialManager);
    int createTextComponent(const std::string& text, const std::string& fontName, glm::vec2 position, float scale,
                            glm::vec3 color);
    void removeTextComponent(int textComponentID);
    void updateTextComponent(int textComponentID, std::string& newText);
    std::shared_ptr<TextComponent> getTextComponent(int textComponentID);

   private:
    MaterialManager& materialManager;
    FontSystem fontSystem;

    std::unordered_map<int, std::shared_ptr<TextComponent>> textComponents;

    int nextComponentID = 0;
};

#endif
