#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

#include "CoreEngine.h"

namespace Toolkit
{
class FileManager {
   private:
   public:
      static std::vector<std::string>  getFiles(const std::string& directory, const std::string& extension);
      static nlohmann::json            loadJson(const std::string& filePath);
};
}
#endif