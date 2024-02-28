#include "Logger.hpp"

LoggerInitException::LoggerInitException(const char* reason, const char* file, int line)
    : etl::exception(reason, file, line) {}

// template <typename DerivedBackend_t, typename LogMessage_t>
// template<typename... Args>
// void Log<DerivedBackend_t, LogMessage_t>::Info(LogMessage_t message, Args&&... args)
// {
//     backend.Info(message, etl::forward<Args>(args)...);
// }

// template <typename DerivedBackend_t, typename LogMessage_t>
// template<typename... Args>
// void Log<DerivedBackend_t, LogMessage_t>::Warn(LogMessage_t message, Args&&... args)
// {
//     backend.Warn(message, etl::forward<Args>(args)...);
// }

// template <typename DerivedBackend_t, typename LogMessage_t>
// template<typename... Args>
// void Log<DerivedBackend_t, LogMessage_t>::Error(LogMessage_t message, Args&&... args)
// {
//     backend.Error(message, etl::forward<Args>(args)...);
// }

// template <typename DerivedBackend_t, typename LogMessage_t>
// void Logger<DerivedBackend_t, LogMessage_t>::ThrowIfInvalid() {
//     ETL_ASSERT(LogSingleton::is_valid(), LOGGER_INIT_EXCEPTION("Log not initialized, call ESP_LOG_INIT"));
// }

template <typename DerivedBackend_t>
template<typename... Args>
void Logger<DerivedBackend_t>::Info(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    //ThrowIfInvalid();
    static_cast<DerivedBackend_t*>(myLogBackend)->Info(message);
}

template <typename DerivedBackend_t>
template<typename... Args>
void Logger<DerivedBackend_t>::Warn(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    static_cast<DerivedBackend_t*>(myLogBackend)->Warn(message);
}

template <typename DerivedBackend_t>
template<typename... Args>
void Logger<DerivedBackend_t>::Error(etl::string<ELSF_LOG_MAX_MESSAGE_LENGTH> message, Args&&... args)
{
    static_cast<DerivedBackend_t*>(myLogBackend)->Error(message);
}

// template <typename DerivedBackend_t, typename LogMessage_t>
// bool LogFactory<DerivedBackend_t, LogMessage_t>::Create(const ILogBackend<DerivedBackend_t, LogMessage_t>& backend)
// {
//     if(!LogSingleton<DerivedBackend_t>::is_valid())
//     {
//         LogSingleton<DerivedBackend_t>::create(backend);
//         return true;
//     }
//     else
//     {
//         throw LoggerInitException("Log already initialized", __FILE__, __LINE__);
//     }
// }

//CRTP implementation, call the derived class's Info, Warn, and Error methods
// template <typename DerivedBackend_t, typename LogMessage_t>
// template <typename... Args>
// void ILogBackend<DerivedBackend_t, LogMessage_t>::Info(LogMessage_t message, Args &&...args) const
// {
//     static_cast<DerivedBackend_t*>(this)->Info(message, etl::forward<Args>(args)...);
// }

// template <typename DerivedBackend_t, typename LogMessage_t>
// template <typename... Args>
// void ILogBackend<DerivedBackend_t, LogMessage_t>::Warn(LogMessage_t message, Args &&...args) const
// {
//     static_cast<DerivedBackend_t*>(this)->Warn(message, etl::forward<Args>(args)...);
// }

// template <typename DerivedBackend_t, typename LogMessage_t>
// template <typename... Args>
// void ILogBackend<DerivedBackend_t, LogMessage_t>::Error(LogMessage_t message, Args &&...args) const
// {
//     static_cast<DerivedBackend_t*>(this)->Error(message, etl::forward<Args>(args)...);
// }


// Explicit template instantiation
// template class Log<ELSF_LOG_MAX_MESSAGE_LENGTH>;
// template class Logger<ELSF_LOG_MAX_MESSAGE_LENGTH>;
// template class LogFactory<ELSF_LOG_MAX_MESSAGE_LENGTH>;
