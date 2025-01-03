#pragma once

#include <mutex>
#include <set>
#include <sstream>
#include <iostream>

#include "LogDefinitions.h"

namespace Log {
    
class Logger {
    private:
        Logger();
        std::mutex                              mtx;
        static LogLevel                         logLevel;
        std::set<LogCategory>                   activeCategories;


        template <typename T> void replacePlaceholder(std::string &format, T value)
        {
            size_t pos = format.find("{}");
            if (pos != std::string::npos) {
                std::stringstream ss;
                ss << value;
                format.replace(pos, 2, ss.str());
            }
        }

        template <typename T, typename... Args> std::string formatString(std::string format, T value, Args... args)
        {
            replacePlaceholder(format, value);
            return formatString(format, args...);
        }

        std::string formatString(const std::string &format) 
        {
            return format;
        }

    public:
        Logger(const Logger &)                  = delete;
        Logger &operator=(const Logger &)       = delete;

        static Logger &getInstance()
        {
            static Logger instance;
            return instance;
        }

        void setLogLevel(LogLevel level)
        {
            logLevel = level;
            log(Log::System, Log::Engine, "Active log level: {}", levelStrings[logLevel]);
        };

        void addCategory(LogCategory category)
        { 
            activeCategories.insert(category);
        }

        void clearCategories() { activeCategories.clear(); }

        template <typename... Args>
        void log(LogLevel level, LogCategory category, const std::string &format, Args... args)
        {
            if (level < logLevel) {
                return;
            }
            if (activeCategories.find(category) == activeCategories.end()) {
                return;
            }

            std::string levelMark               = std::string(levelStrings[level]);
            std::string categoryMark            = "[" + std::string(categoryStrings[category]) + "]";
            std::string marker                  = levelMark + "::" + categoryMark + " ";

            std::string result = formatString(format, args...);
            std::cout << marker << result << std::endl;
        }

        template <typename T>
        void quicklog(T value)
        {
            std::stringstream ss;
            ss << value;
            std::cout << std::string(levelStrings[1]) << "::" << "[local] " << ss.str() << std::endl;
        }

        template <typename... Categories> void addCategories(Categories... categories)
        {
            if constexpr(sizeof...(categories) > 0)
            {
                clearCategories();
                (activeCategories.insert(categories), ...);

                std::stringstream ss;
                ((ss << categoryStrings[static_cast<size_t>(categories)] << ", "), ...);
                log(Log::System, Log::Engine, "Active log categories: " + ss.str());
            }
        }
};
}

#define Log_(level, category, format, ...)      Log::Logger::getInstance().log(level, category, format, __VA_ARGS__);
#define Log__(format)                           Log::Logger::getInstance().quicklog(format);
#define LogLevel(level)                         Log::Logger::getInstance().setLogLevel(level);
#define LogCategories(...)                      Log::Logger::getInstance().addCategories(__VA_ARGS__)
