
#include "Logging/Logger.hpp"
#include "etl_profile.h"

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