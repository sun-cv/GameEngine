#include "Log.h"

Log::Logger::Logger()
{
    for (int category = Engine; category < Count; category++)
    {
        activeCategories.insert(static_cast<LogCategory>(category));
    }
};

Log::LogLevel Log::Logger::logLevel = Log::LogLevel::System;