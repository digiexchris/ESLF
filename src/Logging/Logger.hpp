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

template <typename Derived_t, typename LogMessage_t>
class ILogBackend
{
public:
    virtual ~ILogBackend() {};

    template<typename... Args>
    void Info(LogMessage_t message, Args&&... args) const;

    template<typename... Args>
    void Warn(LogMessage_t message, Args&&... args) const;

    template<typename... Args>
    void Error(LogMessage_t message, Args&&... args) const;
};

template <typename DerivedBackend_t, typename LogMessage_t>
class Log
{
public:
    Log(const ILogBackend<DerivedBackend_t, LogMessage_t>& aBackend) : backend(aBackend) {}
    Log() = delete;
    template<typename... Args>
    void Info(LogMessage_t message, Args&&... args);

    template<typename... Args>
    void Warn(LogMessage_t message, Args&&... args);

    template<typename... Args>
    void Error(LogMessage_t message, Args&&... args);
private:
    const ILogBackend<DerivedBackend_t, LogMessage_t>& backend;
};

template <typename T>
using LogSingleton = etl::singleton<Log<T,etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH>>>;


/**
This is the frontend to the macro, used for intermediate checks
to see if the singleton is in a good state before executing
the log call to it*/
template <typename DerivedBackend_t, typename LogMessage_t>
class Logger
{
public:
    template<typename... Args>
    static void Info(LogMessage_t message, ...);

    template<typename... Args>
    static void Warn(LogMessage_t message, ...);

    template<typename... Args>
    static void Error(LogMessage_t message, ...);

private:
    static void ThrowIfInvalid();
};

template <typename DerivedBackend_t, typename LogMessage_T>
class LogFactory
{   
public:
    static bool Create(const ILogBackend<DerivedBackend_t, LogMessage_T>& backend);
};
