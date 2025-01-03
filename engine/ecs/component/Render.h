#pragma once

#include "Component.h"

#include "Material.h"
#include "Mesh.h"

class Render : public Component
{
    private:
    public:
        bool state                              = true;

        std::string mesh                        = "";
        std::string material                    = "";

        unsigned int layer                      = 0;

};
