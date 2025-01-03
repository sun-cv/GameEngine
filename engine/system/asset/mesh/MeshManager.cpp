#include "MeshManager.h"

#include <nlohmann/json.hpp>

MeshManager::MeshManager()
{
    Log_(Log::System, Log::mMesh, "initializing..");
    cacheMeshes();
    Log_(Log::System, Log::mMesh, "Initialized successfully!");
}

void MeshManager::cacheMeshes()
{
    try
    {
        auto files = Toolkit::FileManager::getFiles(meshDirectory, ".json");

        for (const auto& filepath : files)
        {
            std::string name = std::filesystem::path(filepath).stem().string();
            loadMeshData(name, filepath);
        }
    } 
    catch(Exceptions)
    {
        Log_(Log::Error, Log::mMesh, error.what())
    }
}


VertexBufferLayout MeshManager::parseLayout(nlohmann::json data)
{
    try
    {  
        VertexBufferLayout layout;

        if (!data.contains("layout"))
        {
            Throw_(Error::runtime, "Layout not found in JSON")
        }   

        for (const auto& element : data["layout"])
            { 
                std::string type = element["type"]; unsigned int count = element["count"];

                     if (type == "float")            layout.push<float>(count); 
                else if (type == "unsigned int")     layout.push<unsigned int>(count); 
                else if (type == "unsigned char")    layout.push<unsigned char>(count); 
                else 
                { 
                    Log_(Log::Error, Log::mFile, "Unknown type in layout parse: {}", type); 
                } 
            } 
        return layout;
    }
    catch(...)
    {
        throw;
    }
}

void MeshManager::loadMeshData(const std::string name, std::string filepath)
{
    try
    { 
        auto data = Toolkit::FileManager::loadJson(filepath);
        if (data.empty())
        {
            Throw_(Error::runtime, "No data found at filepath: {}", filepath);
        }

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        VertexBufferLayout layout = parseLayout(data);

        vertices  = data["vertices"].get<std::vector<float>>();
        indices   = data["indices"] .get<std::vector<unsigned int>>();

        loadMesh(name, vertices, indices, layout);
    }
    catch(...)
    {
        throw;
    }
}

std::shared_ptr<Mesh> MeshManager::loadMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, VertexBufferLayout& layout)
{
    Log_(Log::System, Log::Mesh, "Loading mesh: {}", name);

    auto iterator = nameRegistry.find(name);
    if (iterator != nameRegistry.end())
    {
        return meshRegistry[iterator->second];
    }

    try 
    {
        auto mesh = std::make_shared<Mesh>(name, vertices, indices, layout);
        mesh->ID  = generateID();

        nameRegistry[name]      = mesh->ID;
        meshRegistry[mesh->ID]  = mesh;

        return mesh;
    } 
    catch(Exceptions) 
    {
        Throw_(Error::runtime, "Failed to load mesh {}\n exception: {}", name, error.what());
    }
}

unsigned int MeshManager::generateID()
{
    static unsigned int count = 0;
    return count++;
}

bool MeshManager::hasMesh(const std::string& name)
{
    return nameRegistry.find(name) != nameRegistry.end();
}


std::shared_ptr<Mesh> MeshManager::getMesh(const std::string& name)
{
    if (!hasMesh(name))
    {
        Throw_(Error::runtime, "Mesh {} not found", name)
    }
    
    return meshRegistry[nameRegistry[name]];
}

void MeshManager::removeMesh(const std::string & name)
{
    auto iterator = meshRegistry.find(nameRegistry[name]);
    if (iterator == meshRegistry.end())
    {
        Log_(Log::Debug, Log::mTexture, "Unable to remove mesh {} (does not exist)", name);
        return;
    }
    meshRegistry.erase(iterator->first);
}

void MeshManager::clear()
{
    nameRegistry.clear();
    meshRegistry.clear();
    Log_(Log::System, Log::mMesh, "All materials cleared");
}