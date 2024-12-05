#include "EngineCore.h"
#include "FontAtlas.h"

struct TextComponent {
    std::string text;
    Vector3 color;                         // RGB color
    float scale;                           // Text scale
    std::shared_ptr<FontAtlas> fontAtlas;  // Font data
};
