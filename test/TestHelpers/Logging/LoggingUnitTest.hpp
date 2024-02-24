
#include "Logging/Logger.hpp"

class LoggerTest {
protected:
    LoggerTest() {
        if(LogSingleton::is_valid()) {
            LogSingleton::destroy();
        }
    }

    ~LoggerTest() {
        if(LogSingleton::is_valid()) {
            LogSingleton::destroy();
        }
    }
};