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

#define ELSF_LOG_INIT(...) Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Init(__VA_ARGS__)
#define ELSF_LOG_INFO(...) Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Info(__VA_ARGS__)
#define ELSF_LOG_WARN(...) Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Warn(__VA_ARGS__)
#define ELSF_LOG_ERROR(...) Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>::Error(__VA_ARGS__)

#define LOGGER_INIT_EXCEPTION(reason) LoggerInitException((reason), __FILE__, __LINE__)

class LoggerInitException : public etl::exception
{
public:
    LoggerInitException(const char* reason, const char* file, int line)
        : etl::exception(reason, file, line) {}
};


template <size_t MaxMessageLength>
class ILogBackend
{
public:
    virtual ~ILogBackend() = default;
    virtual void Info(etl::string<MaxMessageLength> message, ...) = 0;
    virtual void Warn(etl::string<MaxMessageLength> message, ...) = 0;
    virtual void Error(etl::string<MaxMessageLength> message, ...) = 0;
};




/**
 * LOG
*/
template <size_t S>
class Log// : public etl::singleton<Log<S>>
{
public:

    static void Init(ILogBackend<S>* backend) {
        LogSingleton::create();
        LogSingleton::instance().SetBackend(backend);
    }
    void SetBackend(ILogBackend<S>* aBackend) 
    {
        if(aBackend == nullptr)
        {
            throw LoggerInitException("Log backend cannot be null", __FILE__, __LINE__);
        }
        
        backend = etl::unique_ptr<ILogBackend<S>>(aBackend);
        backendSet = true;
    };

    ILogBackend<S>* GetBackend() 
    {
        return backend.get();
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
        ETL_ASSERT(backendSet, LOGGER_INIT_EXCEPTION("Log backend not set, call ESP_LOG_INIT"));
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
    etl::unique_ptr<ILogBackend<S>> backend;
    bool backendSet;
};

using LogSingleton = etl::singleton<Log<ELSF_LOG_MAX_MESSAGE_LENGTH>>;

template <size_t S>
class Logger 
{
    public:
        static void ThrowIfInvalid() {
                ETL_ASSERT(LogSingleton::is_valid(), LOGGER_INIT_EXCEPTION("Log backend not set, call ESP_LOG_INIT"));
                ETL_ASSERT(LogSingleton::instance().IsBackendSet(), LOGGER_INIT_EXCEPTION("Log backend not set, call ESP_LOG_INIT"));;
        }

        static void Info(etl::string<S> message, ...) {
            ThrowIfInvalid();
            va_list args;
            va_start(args, message);
            LogSingleton::instance().Info(message, args);
        }

        static void Warn(etl::string<S> message, ...) {
            ThrowIfInvalid();
            va_list args;
            va_start(args, message);
            LogSingleton::instance().Warn(message, args);
        }

        static void Error(etl::string<S> message, ...) {
            ThrowIfInvalid();
            va_list args;
            va_start(args, message);
            LogSingleton::instance().Error(message, args);
        }

        static void Init(ILogBackend<S>* backend) {
            if(!LogSingleton::is_valid())
            {
                LogSingleton::create();
            }
            else
            {
                LogSingleton::destroy();
                LogSingleton::create();
            }

            LogSingleton::instance().Init(backend);
        }
};