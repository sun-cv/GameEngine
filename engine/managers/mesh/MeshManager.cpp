#include "MeshManager.h"

MeshManager::MeshManager() { initialize(); }

void MeshManager::initialize() {
    std::cout << "[SYSTEM]::[MESHMANAGER] Starting Mesh Manager..." << std::endl;
    cacheDefaultMeshes();
    std::cout << "[SYSTEM]::[MESHMANAGER] Loaded successfully." << std::endl;
}

void MeshManager::cacheDefaultMeshes() {
    for (const auto& filePath : FileManager::getFiles(meshDirectory, ".json")) {
        std::string name = std::filesystem::path(filePath).stem().string();
        loadMesh(name, filePath);
    }
}

std::shared_ptr<Mesh> MeshManager::loadMesh(const std::string& name, const std::string& filePath) {
    if (hasMeshByName(name)) {
        std::cerr << "[NOTICE]::[MESHMANAGER] Mesh already loaded: " << name << std::endl;
        return getMeshByName(name);
    }

    try {
        auto jsonData = FileManager::loadJson(filePath);
        if (!jsonData.contains("vertices") || !jsonData.contains("indices")) {
            std::cerr << "[FAILED]::[MESHMANAGER] Invalid file format: " << filePath << std::endl;
            return nullptr;
        }

        std::vector<float> vertices = jsonData["vertices"].get<std::vector<float>>();
        std::vector<unsigned int> indices = jsonData["indices"].get<std::vector<unsigned int>>();

        auto mesh = std::make_shared<Mesh>(vertices, indices);
        mesh->ID = addMesh(mesh, name);

        std::cout << "[SYSTEM]::[MESHMANAGER] Successfully loaded mesh: " << name << std::endl;
        return mesh;

    } catch (const std::exception& e) {
        std::cerr << "[FAILED]::[MESHMANAGER] Error loading mesh: " << e.what() << "\n";
        return nullptr;
    }
}

std::string MeshManager::addMesh(const std::shared_ptr<Mesh>& mesh, const std::string& name) {
    std::string id = generateUniqueID(name);

    if (meshRegistry.contains(id)) {
        std::cerr << "[NOTICE]::[MESHMANAGER] Mesh ID already exists: " << id << std::endl;
        return id;
    }

    if (!name.empty()) {
        nameToIDMap[name] = id;
    }

    meshRegistry[id] = {mesh, name};
    return id;
}

std::shared_ptr<Mesh> MeshManager::getMeshByID(const std::string& id) const {
    if (!validateMeshExists(id)) {
        return nullptr;
    }
    return meshRegistry.at(id).mesh;
}

std::shared_ptr<Mesh> MeshManager::getMeshByName(const std::string& name) const {
    auto it = nameToIDMap.find(name);
    if (it == nameToIDMap.end()) {
        std::cerr << "[NOTICE]::[MESHMANAGER] Mesh name not found: " << name << std::endl;
        return nullptr;
    }
    return getMeshByID(it->second);
}

bool MeshManager::hasMeshByID(const std::string& id) const { return meshRegistry.contains(id); }

bool MeshManager::hasMeshByName(const std::string& name) const { return nameToIDMap.contains(name); }

void MeshManager::removeMeshByID(const std::string& id) {
    if (!validateMeshExists(id)) {
        return;
    }

    auto& entry = meshRegistry[id];
    if (!entry.name.empty()) {
        nameToIDMap.erase(entry.name);
    }

    meshRegistry.erase(id);
}

void MeshManager::clear() {
    meshRegistry.clear();
    nameToIDMap.clear();
}

void MeshManager::addInstanceTransform(const std::string& id, const glm::mat4& transform) {
    if (!validateMeshExists(id)) {
        return;
    }
    meshRegistry[id].instanceTransforms.push_back(transform);
}

const std::vector<glm::mat4>& MeshManager::getInstanceTransforms(const std::string& id) const {
    return meshRegistry.at(id).instanceTransforms;
}

std::string MeshManager::generateUniqueID(const std::string& name) const {
    static size_t counter = 0;
    std::ostringstream oss;
    oss << (name.empty() ? "mesh" : name) << "_" << counter++;
    return oss.str();
}

bool MeshManager::validateMeshExists(const std::string& id) const {
    if (!hasMeshByID(id)) {
        std::cerr << "[NOTICE]::[MESHMANAGER] Mesh ID not found: " << id << std::endl;
        return false;
    }
    return true;
}
