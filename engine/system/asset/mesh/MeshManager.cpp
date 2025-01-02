#include "MeshManager.h"

MeshManager::MeshManager()
{
    Log_(Log::System, Log::mMesh, "initializing..");
    cacheMeshes();
    Log_(Log::System, Log::mMesh, "Initialized successfully!");
}

void MeshManager::cacheMeshes()
{
    auto files = Toolkit::FileManager::getFiles(meshDirectory, ".json");

    
    for (const auto& filepath : files)
    {
        std::string name = std::filesystem::path(filepath).stem().string();
        loadMesh(name, filepath);
    }
}


VertexBufferLayout MeshManager::parseLayout(nlohmann::json data)
{
    VertexBufferLayout layout;

    if (!data.contains("layout"))
    {
        Log_(Log::Error, Log::mFile, "Layout not found in JSON"); 
        return layout;
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


std::shared_ptr<Mesh> MeshManager::loadMesh(const std::string & name, const std::string & filepath)
{
    Log_(Log::Trace, Log::mMaterial, "Caching mesh {} ", name);

    auto iterator = nameRegistry.find(name);
    if (iterator != nameRegistry.end())
    {
        Log_(Log::Debug, Log::mTexture, "Mesh {} already loaded", name);
        MeshEntry buffer = meshRegistry[iterator->second];
        return buffer.mesh;
    }

    try
    {
        auto data = Toolkit::FileManager::loadJson(filepath);
        if (data.empty())
        {
            return nullptr;
        }
        
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        VertexBufferLayout layout = parseLayout(data);

        vertices  = data["vertices"].get<std::vector<float>>();
        indices   = data["indices"] .get<std::vector<unsigned int>>();

        auto mesh = std::make_shared<Mesh>(data["name"], vertices, indices, layout);
        mesh->ID  = addMesh(name, mesh);
        return mesh;
        
    }
    catch(const std::exception& error)
    {
        Log_(Log::Error, Log::mMesh, "Failed to load mesh {} from file: {} \n exception: {}", name, filepath, error.what());
        return nullptr;
    }
}

unsigned int MeshManager::addMesh(const std::string name, std::shared_ptr<Mesh> mesh)
{
    auto id = generateID();

    nameRegistry[name] = id;
    meshRegistry[id]   = { name, mesh };

    return id;
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
        Log_(Log::Error, Log::mMesh, "Mesh {} not found", name);
        return nullptr;
    }
    
    auto meshEntry = meshRegistry[nameRegistry[name]];
    return meshEntry.mesh;
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
