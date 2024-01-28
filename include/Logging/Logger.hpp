/**
 * @file ILogger.hpp
 * @brief This file defines the interface for the logger.
 * Override the log backend with a custom implementation,
 * and instantiate the Log with that backend.
 * 
 * An example implementation is in test/TestHelpers/Logging/TestLogBackend.hpp
 * 
 * If you wanted to write a logger for the ESP32, you could replace the calls to
 * PrintLog() in TestLogBackend::Log(), TestLogBackend::Info(), etc...
 * with the appropriate ESP32 logging functions, like ESP_LOGI, ESP_LOGE, etc...
 * 
 * See test/setup.cpp for an example of how to set the backend.
*/

#pragma once

#include <etl/string.h>
#include <etl/singleton.h>
#include <stdarg.h>

#define ELSF_LOG_MAX_MESSAGE_LENGTH 256

#define ELSF_LOG_INIT(...) LogSingleton::instance().SetBackend(__VA_ARGS__)
#define ELSF_LOG_INFO(...) LogSingleton::instance().Info(__VA_ARGS__)
#define ELSF_LOG_WARN(...) LogSingleton::instance().Warn(__VA_ARGS__)
#define ELSF_LOG_ERROR(...) LogSingleton::instance().Error(__VA_ARGS__)

class LoggerInitException : public etl::exception
{
};

template <size_t MaxMessageLength>
class ILogBackend
{
public:
    virtual void Info(etl::string<MaxMessageLength> message, ...) = 0;
    virtual void Warn(etl::string<MaxMessageLength> message, ...) = 0;
    virtual void Error(etl::string<MaxMessageLength> message, ...) = 0;
};



template <size_t S>
class Log// : public etl::singleton<Log<S>>
{
public:
    
    ~Log(){
        delete backend;
    }

    static void Init(ILogBackend<S>* backend) {
        LogSingleton::create();
        LogSingleton::instance().SetBackend(backend);
    }
    void SetBackend(ILogBackend<S>* aBackend) 
    {
        backend = aBackend;
        backendSet = true;
    };

    void Info(etl::string<S> message, ...)
    {
        ThrowIfBackendNotSet();

        va_list args;
        va_start(args, message);
        backend->Info(message, args);
    }

    void Warn(etl::string<S> message, ...)
    {
        ThrowIfBackendNotSet();

        va_list args;
        va_start(args, message);
        backend->Warn(message, args);
    }

    void Error(etl::string<S> message, ...)
    {
        ThrowIfBackendNotSet();

        va_list args;
        va_start(args, message);
        backend->Error(message, args);
    }

    void ThrowIfBackendNotSet() 
    {
        ETL_ASSERT(backendSet, ETL_ERROR_WITH_VALUE(ETL_ERROR(LoggerInitException),"Log backend not set, call ESP_LOG_INIT"));
        // if(!backendSet)
        // {
        //     throw etl::exception("Log backend not set, call ESP_LOG_INIT");
        // }
    
    };
    bool IsBackendSet()
    {
        return backendSet;
    }
private:
    ILogBackend<S>* backend;
    bool backendSet;
};

using LogSingleton = etl::singleton<Log<ELSF_LOG_MAX_MESSAGE_LENGTH>>;