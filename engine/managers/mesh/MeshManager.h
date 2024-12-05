#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>
#include "EngineCore.h"
#include "FileManager.h"
#include "Mesh.h"

class MeshManager {
   public:
    // Constructor
    MeshManager();

    // Initialization
    void initialize();

    // Mesh Management
    std::shared_ptr<Mesh> loadMesh(const std::string& name, const std::string& filePath);
    std::shared_ptr<Mesh> getMeshByID(const std::string& id) const;
    std::shared_ptr<Mesh> getMeshByName(const std::string& name) const;
    bool hasMeshByID(const std::string& id) const;
    bool hasMeshByName(const std::string& name) const;
    void removeMeshByID(const std::string& id);
    void clear();

    // Instance Transforms
    void addInstanceTransform(const std::string& id, const glm::mat4& transform);
    const std::vector<glm::mat4>& getInstanceTransforms(const std::string& id) const;

   private:
    // Helper Functions
    void cacheDefaultMeshes();
    std::string addMesh(const std::shared_ptr<Mesh>& mesh, const std::string& name);
    std::string generateUniqueID(const std::string& name) const;
    bool validateMeshExists(const std::string& id) const;

    // Members
    std::string meshDirectory = "D:/Projects/GameEngine/assets/mesh";

    struct MeshEntry {
        std::shared_ptr<Mesh> mesh;
        std::string name;
        std::vector<glm::mat4> instanceTransforms;
    };

    std::unordered_map<std::string, MeshEntry> meshRegistry;   // Map of mesh ID to MeshEntry
    std::unordered_map<std::string, std::string> nameToIDMap;  // Map of mesh name to mesh ID
};

#endif  // MESH_MANAGER_H