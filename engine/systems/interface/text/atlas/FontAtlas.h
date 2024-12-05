#ifndef FONT_ATLAS_H
#define FONT_ATLAS_H

#include "EngineCore.h"
#include "MaterialComponent.h"

struct Glyph {
    glm::vec2 uvStart;
    glm::vec2 uvEnd;
    glm::vec2 size;
    glm::vec2 bearing;
    float advance;
};

class FontAtlas {
   public:
    FontAtlas(std::string name, std::shared_ptr<MaterialComponent> material, int width, int height, int rows,
              int columns);

    void loadGlyphData(const std::unordered_map<char, Glyph>& glyphData);  // external
    const Glyph* getGlyph(char c) const;

    std::shared_ptr<MaterialComponent> getMaterial() const { return atlasMaterial; }

   private:
    std::shared_ptr<MaterialComponent> atlasMaterial;      // The font atlas texture
    int atlasWidth, atlasHeight, atlasRows, atlasColumns;  // Dimensions of the atlas
    std::unordered_map<char, Glyph> glyphs;                // Metadata for each glyph
};

#endif
