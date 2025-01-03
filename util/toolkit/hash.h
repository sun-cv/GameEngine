#pragma once

#include <string>
#include <tuple>
#include <functional>
#include "CoreUtility.h"

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>()(pair.first);
        auto hash2 = std::hash<T2>()(pair.second);
        return hash1 ^ (hash2 << 1);
    }
};


struct GroupKeyHash {
    std::size_t operator()(const std::tuple<std::string, std::string, int>& key) const {
        auto hash1 = std::hash<std::string>()(std::get<0>(key));
        auto hash2 = std::hash<std::string>()(std::get<1>(key));
        auto hash3 = std::hash<int>()(std::get<2>(key));

        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
    }
};


class Hash
{
    private:
    public:

};