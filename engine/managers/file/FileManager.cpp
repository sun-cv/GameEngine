
#include "FileManager.h"

std::vector<std::string> FileManager::getFiles(const std::string& directory,
                                               const std::string& extension) {
    std::vector<std::string> files;

    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file() && entry.path().extension() == extension) {
                files.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& error) {
        std::cout << "[FAILED]::[FILEMANAGER] Error traversing directory: " << error.what()
                  << std::endl;
    }
    return files;
}

nlohmann::json FileManager::loadJson(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "[FAILED]::[FILEMANAGER] Failed to open file: " << filePath << std::endl;
        return {};
    }

    nlohmann::json jsonData;
    file >> jsonData;
    return jsonData;
}
