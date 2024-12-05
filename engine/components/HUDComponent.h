#include "EngineCore.h"
#include "Entity.h"

struct HUDComponent {
    Entity::Handle linkedEntity;  // Optional link to game entity (e.g., health bar for player)
    Vector4 backgroundColor;      // Optional background color
    Vector4 borderColor;          // Optional border color
    float borderThickness;        // Optional border thickness
};
