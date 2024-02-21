#pragma once

#include "Logging/Logger.hpp"
#include <etl/string.h>
#include <stdarg.h>
#include "Helpers.hpp"

template <size_t MaxMessageLength, size_t MaxPrefixLength>
class TestLogBackend : public ILogBackend<MaxMessageLength>
{
public:

    virtual void Info(etl::string<MaxMessageLength> message, ...) const override
    {
        va_list args;
        va_start(args, message);
        PrintLog("INFO: ", message, args);
    }

    virtual void Warn(etl::string<MaxMessageLength> message, ...) const override
    {
        va_list args;
        va_start(args, message);
        PrintLog("WARN: ", message, args);
    }

    virtual void Error(etl::string<MaxMessageLength> message, ...) const override
    {
        va_list args;
        va_start(args, message);
        PrintLog("ERROR: ", message, args);
    }

    //allow each log function to add up to 32 characters of prefix (eg. ERROR: WARN: FILENAME:, etc...)
    void PrintLog(etl::string<MaxPrefixLength> prefix, etl::string<MaxMessageLength> message, va_list args) const
    {
        
        #ifdef APPLICATION_LOGGING_OUTPUT
            etl::string<MaxMessageLength+MaxPrefixLength> output;
            snprintf(output.data(), output.max_size(), message.c_str(), args);
            printf("%s%s",prefix.c_str(), message.c_str());
        #else
            ELSF_UNUSED(prefix);
            ELSF_UNUSED(message);
        #endif
    }
};