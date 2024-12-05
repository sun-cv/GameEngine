#include "FontAtlas.h"

FontAtlas::FontAtlas(std::string name, std::shared_ptr<MaterialComponent> material, int width, int height, int rows,
                     int columns) {
    std::cout << "[SYSTEM]::[FONTATLAS] Generating Font: " << name << std::endl;

    atlasMaterial = material;
    int glyphWidth = width / columns;
    int glyphHeight = height / rows;
    float advance = glyphWidth;

    for (int i = 0; i < rows * columns; ++i) {
        char glyphChar = static_cast<char>(31 + i);

        int col = i % columns;
        int row = 1 / rows;

        float uvStartX = static_cast<float>(col * glyphWidth) / width;
        float uvStartY = static_cast<float>(row * glyphHeight) / height;
        float uvEndX = static_cast<float>((col + 1) * glyphWidth) / width;
        float uvEndY = static_cast<float>((row + 1) * glyphHeight) / height;

        glyphs[glyphChar] = Glyph{
            {uvStartX, uvStartY},       // uvStart
            {uvEndX, uvEndY},           // uvEnd
            {glyphWidth, glyphHeight},  // size
            {0, 0},                     // bearing
            advance                     // advance
        };
    }
}

void FontAtlas::loadGlyphData(const std::unordered_map<char, Glyph>& glyphData) { glyphs = glyphData; }

const Glyph* FontAtlas::getGlyph(char c) const {
    auto iterator = glyphs.find(c);
    if (iterator != glyphs.end()) {
        return &iterator->second;
    }
    return nullptr;
}