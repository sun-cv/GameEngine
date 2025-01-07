#pragma once

#include "CoreUtility.h"
#include "CoreToolkit.h"


#include "Mesh.h"

class MeshManager
{   // Variables
    private:
        std::string meshDirectory               = "D:/Projects/Active/GameEngine/assets/mesh";
        
        std::unordered_map<
            unsigned int,
            std::shared_ptr<Mesh>
            >                                   meshRegistry;
        std::unordered_map<
            std::string,
            unsigned int
            >                                   nameRegistry;
    // Functions
    private: // Initialization
        void cacheMeshes();

            // Helper
        void loadMeshData(const std::string name, std::string filepath);
        unsigned int generateID();
        VertexBufferLayout parseLayout(nlohmann::json data);

    public:
            // Access
        std::shared_ptr<Mesh> loadMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, VertexBufferLayout& layout);
        std::shared_ptr<Mesh> getMesh (const std::string& name);
                         bool hasMesh (const std::string& name);
            // Release
        void removeMesh(const std::string& id);
        void clear();

    public:
        MeshManager();
       ~MeshManager();
};

