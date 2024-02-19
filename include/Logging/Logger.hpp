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

#define ELSF_LOG_INIT(...) LogFactory<ELSF_LOG_MAX_MESSAGE_LENGTH>::Create(__VA_ARGS__)
#define ELSF_LOG_INFO(...) Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Info(__VA_ARGS__)
#define ELSF_LOG_WARN(...) Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Warn(__VA_ARGS__)
#define ELSF_LOG_ERROR(...) Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Error(__VA_ARGS__)

#define LOGGER_INIT_EXCEPTION(reason) LoggerInitException((reason), __FILE__, __LINE__)

class LoggerInitException : public etl::exception
{
public:
    LoggerInitException(const char* reason, const char* file, int line);
};

template <size_t MaxMessageLength>
class ILogBackend
{
public:
    virtual ~ILogBackend() {};
    virtual void Info(etl::string<MaxMessageLength> message, ...) = 0;
    virtual void Warn(etl::string<MaxMessageLength> message, ...) = 0;
    virtual void Error(etl::string<MaxMessageLength> message, ...) = 0;
};

template <size_t S>
class Log
{
public:
    void SetBackend(ILogBackend<S>* aBackend);
    ILogBackend<S>* GetBackend();
    void Info(etl::string<S> message, ...);
    void Warn(etl::string<S> message, ...);
    void Error(etl::string<S> message, ...);
    bool IsBackendSet();
private:
    void ThrowIfBackendNotSet();
    

    etl::unique_ptr<ILogBackend<S>> backend;
    bool backendSet = false;
};

using LogSingleton = etl::singleton<Log<ELSF_LOG_MAX_MESSAGE_LENGTH>>;


/**
This is the frontend to the macro, used for intermediate checks
to see if the singleton is in a good state before executing
the log call to it*/
template <size_t S>
class Logger
{
public:
    static void Info(etl::string<S> message, ...);
    static void Warn(etl::string<S> message, ...);
    static void Error(etl::string<S> message, ...);

private:
    static void ThrowIfInvalid();
};

template <size_t S>
class LogFactory
{   
public:
    static bool Create(ILogBackend<S>* backend);
};
