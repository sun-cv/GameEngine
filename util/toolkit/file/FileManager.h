#pragma once

#include "CoreUtility.h"

#include "FileManagerConversions.h"

namespace Toolkit
{
class FileManager {
   private:
   public:
      static std::vector<std::string>  getFiles(const std::string& directory, const std::string& extension);
      static nlohmann::json            loadJson(const std::string& filePath);
};
};