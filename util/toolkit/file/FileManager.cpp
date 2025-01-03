#include "FileManager.h"

#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>


namespace Toolkit
{
std::vector<std::string> FileManager::getFiles(const std::string& directory, const std::string& extension)
{
    std::vector<std::string> files;
    try 
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == extension)
            {
                files.push_back(entry.path().string());
            }
        }
    return files;
    } 
    catch (const std::filesystem::filesystem_error& error) 
    {
        Throw_(Error::runtime, "Failed traversing directory: {} | Exception:\n {}", directory, error.what())
    }

}

nlohmann::json FileManager::loadJson(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()) 
    {
        Throw_(Error::runtime, "Failed to open file: {}", filepath)
        return {};
    }

    nlohmann::json jsonData;
    file >> jsonData;
    return jsonData;
}
}