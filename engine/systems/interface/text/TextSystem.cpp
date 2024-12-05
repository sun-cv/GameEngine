#include "TextSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

TextSystem::TextSystem(MaterialManager& materialManager)
    : materialManager(materialManager), fontSystem(materialManager) {}

int TextSystem::createTextComponent(const std::string& text, const std::string& fontName, glm::vec2 position,
                                    float scale, glm::vec3 color) {
    nextComponentID++;
    auto fontAtlas = fontSystem.getFontAtlas(fontName);
    if (fontAtlas) {
        auto textComponent = std::make_shared<TextComponent>(nextComponentID, text, position, scale, color, fontAtlas);
        textComponent = textComponents[nextComponentID] = textComponent;

        std::cout << "[SYSTEM]::[TEXTSYSTEM] Created TextComponent with ID: " << nextComponentID << "\n";

        return nextComponentID;
    }
    std::cerr << "[FAILED]::[TEXTSYSTEM] Font not found: " << fontName << std::endl;
}

void TextSystem::removeTextComponent(int textComponentID) {
    if (textComponents.erase(textComponentID)) {
        std::cout << "[SYSTEM]::[TEXTSYSTEM] Removed TextComponent with ID: " << textComponentID << "\n";
    } else {
        std::cerr << "[NOTICE]::[TEXTSYSTEM] Failed to find TextComponent with : " << textComponentID << "\n";
    }
}

void TextSystem::updateTextComponent(int textComponentID, std::string& newText) {
    auto iterator = textComponents.find(textComponentID);
    if (iterator == textComponents.end()) {
        std::cout << "[FAILED]::[TEXTSYSTEM] Failed to find TextComponent with ID: " << textComponentID << std::endl;
        return;
    }
    auto textComponent = iterator->second;
    textComponent->text = newText;
}

std::shared_ptr<TextComponent> TextSystem::getTextComponent(int textComponentID) {
    auto iterator = textComponents.find(textComponentID);

    if (iterator == textComponents.end()) {
        std::cout << "[FAILED]::[TEXTSYSTEM] Failed to find TextComponent with ID: " << textComponentID << std::endl;
        return;
    }
    return iterator->second;
}