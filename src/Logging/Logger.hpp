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
#include <fmt/core.h>

constexpr uint16_t ELSF_LOG_MAX_MESSAGE_LENGTH = 256;

#define ELSF_LOG_INIT(BackendPTR) LogSingleton::create(std::move(BackendPTR))
#define ELSF_LOG_INFO(...) LogSingleton::instance().Info(__VA_ARGS__)
#define ELSF_LOG_WARN(...) LogSingleton::instance().Warn(__VA_ARGS__)
#define ELSF_LOG_ERROR(...) LogSingleton::instance().Error(__VA_ARGS__)

#define LOGGER_INIT_EXCEPTION(reason) LoggerInitException((reason), __FILE__, __LINE__)

class LoggerInitException : public etl::exception
{
public:
    using exception::exception;
};

class ILogBackend
{
public:
    //NOTE: any taking in of formatting params happens in the Logger.
    virtual void Info(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const = 0;

    virtual void Warn(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const = 0;
    
    virtual void Error(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message) const = 0;

    virtual ~ILogBackend() = default;
    
};


class Logger
{
public:
    template<typename... Args>
    void Info(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    template<typename... Args>
    void Warn(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    template<typename... Args>
    void Error(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args);

    void SetBackend(ILogBackend* aBackend) {
        ETL_ASSERT(aBackend != nullptr, LOGGER_INIT_EXCEPTION("Log not initialized, call ESP_LOG_INIT"));
        myLogBackend.reset(aBackend);
    }

    ILogBackend* GetBackend() const {
        return myLogBackend.get();
    }

    explicit Logger(ILogBackend* aBackend) {
        SetBackend(aBackend);
    }
protected:

    template <typename... Args>
    etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> ApplyFormat(const etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH>& message, Args&&... args) const;

private:
    etl::unique_ptr<ILogBackend> myLogBackend;
};

using LogSingleton = etl::singleton<Logger>;


template<typename... Args>
void Logger::Info(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    myLogBackend->Info(ApplyFormat(message, etl::forward<Args>(args)...));
}

template<typename... Args>
void Logger::Warn(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    myLogBackend->Warn(ApplyFormat(message, etl::forward<Args>(args)...));
}

template<typename... Args>
void Logger::Error(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    myLogBackend->Error(ApplyFormat(message, etl::forward<Args>(args)...));
}

template <typename... Args>
etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> Logger::ApplyFormat(const etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH>& message, Args&&... args) const
{
    return fmt::format(message.c_str(), etl::forward<Args>(args)...).c_str();
}
