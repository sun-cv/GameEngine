#pragma once

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <stdexcept>

#include "FileManager.h"

namespace nlohmann {

    template <>
    struct adl_serializer<glm::vec3>
    {
        static void from_json(const json& j, glm::vec3& vec) 
        {
            if (!j.is_array() || j.size() != 3) 
            {
                Log_(Log::Error, Log::mFile, "Expected a 3-element array for glm::vec3");
            }
            vec = glm::vec3
            (
                static_cast<float>(j[0].get<double>()),
                static_cast<float>(j[1].get<double>()),
                static_cast<float>(j[2].get<double>())
            );
        }

        static void to_json(json& j, const glm::vec3& vec)
        {
            j = json::array({vec.x, vec.y, vec.z});
        }
    };

    template <>
    struct adl_serializer<glm::vec4> 
    {
        static void from_json(const json& j, glm::vec4& vec) 
        {
            if (!j.is_array() || j.size() != 4) 
            {
                Log_(Log::Error, Log::mFile, "Expected a 4-element array for glm::vec4");
            }
            vec = glm::vec4
            (
                static_cast<float>(j[0].get<double>()),
                static_cast<float>(j[1].get<double>()),
                static_cast<float>(j[2].get<double>()),
                static_cast<float>(j[3].get<double>())
            );
        }

        static void to_json(json& j, const glm::vec4& vec) 
        {
            j = json::array({vec.x, vec.y, vec.z, vec.w});
        }
    };

    template <>
    struct adl_serializer<glm::mat4> 
    {
        static void from_json(const json& j, glm::mat4& mat) 
        {
            if (!j.is_array() || j.size() != 4) 
            {
                Log_(Log::Error, Log::mFile, "Expected a 4x4 array for glm::mat4");
            }

            for (int i = 0; i < 4; ++i) 
            {
                if (!j[i].is_array() || j[i].size() != 4) 
                {
                    Log_(Log::Error, Log::mFile, "Expected a 4-element array for each row of glm::mat4");
                }
                for (int j_col = 0; j_col < 4; ++j_col) 
                {
                    mat[i][j_col] = static_cast<float>(j[i][j_col].get<double>());
                }
            }
        }

        static void to_json(json& j, const glm::mat4& mat) 
        {
            j = json::array();
            for (int i = 0; i < 4; ++i) 
            {
                j.push_back({mat[i][0], mat[i][1], mat[i][2], mat[i][3]});
            }
        }
    };
}
