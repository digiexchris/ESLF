#include "Logging/Logger.hpp"

LoggerInitException::LoggerInitException(const char* reason, const char* file, int line)
    : etl::exception(reason, file, line) {}

template <size_t S>
void Log<S>::Info(etl::string<S> message, ...)
{
    va_list args;
    va_start(args, message);
    backend.Info(message, args);
}

template <size_t S>
void Log<S>::Warn(etl::string<S> message, ...)
{
    va_list args;
    va_start(args, message);
    backend.Warn(message, args);
}

template <size_t S>
void Log<S>::Error(etl::string<S> message, ...)
{
    va_list args;
    va_start(args, message);
    backend.Error(message, args);
}

template <size_t S>
void Logger<S>::ThrowIfInvalid() {
    ETL_ASSERT(LogSingleton::is_valid(), LOGGER_INIT_EXCEPTION("Log not initialized, call ESP_LOG_INIT"));
}

template <size_t S>
void Logger<S>::Info(etl::string<S> message, ...)
{
    ThrowIfInvalid();
    va_list args;
    va_start(args, message);
    LogSingleton::instance().Info(message, args);
}

template <size_t S>
void Logger<S>::Warn(etl::string<S> message, ...)
{
    ThrowIfInvalid();
    va_list args;
    va_start(args, message);
    LogSingleton::instance().Warn(message, args);
}

template <size_t S>
void Logger<S>::Error(etl::string<S> message, ...)
{
    ThrowIfInvalid();
    va_list args;
    va_start(args, message);
    LogSingleton::instance().Error(message, args);
}

template <size_t S>
bool LogFactory<S>::Create(const ILogBackend<S>& backend)
{
    ETL_ASSERT(backend != nullptr, LOGGER_INIT_EXCEPTION("Log backend cannot be null"))
    
    if(!LogSingleton::is_valid())
    {
        LogSingleton::create(backend);
        //LogSingleton::instance().SetBackend(backend);
        return true;
    }
    else
    {
        throw LoggerInitException("Log already initialized", __FILE__, __LINE__);
    }
}

// Explicit template instantiation
template class Log<ELSF_LOG_MAX_MESSAGE_LENGTH>;
template class Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>;
template class LogFactory<ELSF_LOG_MAX_MESSAGE_LENGTH>;
