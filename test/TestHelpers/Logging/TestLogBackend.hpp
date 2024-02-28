#pragma once

#include "Logging/Logger.hpp"
#include <etl/string.h>
#include <stdarg.h>
#include "Helpers.hpp"

#ifdef APPLICATION_LOGGING_OUTPUT
    #include <fmt/core.h>
#endif

class TestLogBackend : public ILogBackend
{
public:

    
    virtual void Info(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const override
    {
        PrintLog("INFO: ", message);
    }

    virtual void Warn(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const override
    {
        PrintLog("WARN: ", message);
    }

    virtual void Error(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const override
    {
        PrintLog("ERROR: ", message);
    }

    //allow each log function to add up to 32 characters of prefix (eg. ERROR: WARN: FILENAME:, etc...)
    void PrintLog(etl::string<8> prefix, etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const
    {
        
        #ifdef APPLICATION_LOGGING_OUTPUT
            fmt::print("{}{}\n", prefix.c_str(), message.c_str());
        #else
            ELSF_UNUSED(prefix);
            ELSF_UNUSED(message);
        #endif
    }
};