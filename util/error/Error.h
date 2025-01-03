#pragma once

#include <stdexcept>
#include <iostream>
#include <sstream>

namespace Error
{

enum ErrorLevel
{
    runtime,
    logic,
    invalid,
    range
};


class ErrorHandler
{
    private:
        ErrorHandler();

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
        ErrorHandler(const ErrorHandler&)               = delete;
        ErrorHandler &operator=(const ErrorHandler&)    = delete;

        static ErrorHandler& getInstance()
        {
            static ErrorHandler instance;
            return instance;
        }

        template <typename... Args>
        [[noreturn]] inline void Throw(ErrorLevel level, const std::string& format, Args... args)
        {
            std::string result = formatString(format, args...);

            switch (level) 
            {
                case Error::runtime:
                    throw std::runtime_error(result);
                case Error::logic:
                    throw std::logic_error(result);
                case Error::invalid:
                    throw std::invalid_argument(result);
                case Error::range:
                    throw std::out_of_range(result);
                default:
                    throw std::runtime_error(result);
            }
        }
};
}

#define Throw_(level, format, ...) Error::ErrorHandler::getInstance().Throw(level, format, __VA_ARGS__);
#define Exceptions const std::exception& error

