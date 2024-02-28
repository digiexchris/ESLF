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

template <typename Derived_t>
class ILogBackend
{
public:
    // virtual ~ILogBackend() {};

    // template<typename... Args>
    // void Info(LogMessage_t message, Args&&... args) const;

    // template<typename... Args>
    // void Warn(LogMessage_t message, Args&&... args) const;

    // template<typename... Args>
    // void Error(LogMessage_t message, Args&&... args) const;
};

// template <typename T>
// using LogSingleton = etl::singleton<Log<T,etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH>>>;


/**
This is the frontend to the macro, used for intermediate checks
to see if the singleton is in a good state before executing
the log call to it*/
template <typename DerivedBackend_t>
class Logger: public etl::singleton<Logger<DerivedBackend_t>>
{
public:
    template<typename... Args>
    void Info(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    template<typename... Args>
    void Warn(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    template<typename... Args>
    void Error(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    void SetBackend(ILogBackend<DerivedBackend_t>* aBackend) {
        myLogBackend.reset(aBackend) = ;
    }

    ILogBackend<DerivedBackend_t>* GetBackend() const {
        return myLogBackend;
    }

protected:
    Logger(ILogBackend<DerivedBackend_t>* aBackend) : myLogBackend(aBackend) {}

private:
    etl::unique_ptr<ILogBackend<DerivedBackend_t>> myLogBackend;
};