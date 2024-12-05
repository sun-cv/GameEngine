#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include "EngineCore.h"

class FileManager {
   public:
    static std::vector<std::string> getFiles(const std::string& directory, const std::string& extension);

    static nlohmann::json loadJson(const std::string& filePath);

   private:
};

#endif