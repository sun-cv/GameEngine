#pragma once

#include "Component.h"

#include "Material.h"
#include "Mesh.h"

class Render : public Component
{
    private:
    public:
        bool state                              = true;

        std::shared_ptr<Mesh>                   mesh;
        std::shared_ptr<Material>               material;

};
