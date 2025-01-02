#pragma once

#include "CoreUtility.h"
#include "CoreToolkit.h"

#include "Mesh.h"

struct MeshEntry {
    std::string name;
    std::shared_ptr<Mesh> mesh;
    std::vector<glm::mat4> instanceTransforms;
};

class MeshManager
{
    private:
        std::string meshDirectory = "D:/Projects/Active/GameEngine/assets/mesh";
        std::unordered_map<unsigned int, MeshEntry>   meshRegistry;
        std::unordered_map<std::string, unsigned int> nameRegistry;

    private:
        void cacheMeshes();

        unsigned int addMesh(const std::string name, std::shared_ptr<Mesh> mesh);
        unsigned int generateID();
        VertexBufferLayout parseLayout(nlohmann::json data);

    public:
        MeshManager();

        std::shared_ptr<Mesh> loadMesh(const std::string& name, const std::string& filepath);
        std::shared_ptr<Mesh> getMesh (const std::string& name);
                         bool hasMesh (const std::string& name);
        
        void removeMesh(const std::string& id);
};
