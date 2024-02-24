#pragma once

#include "Logging/Logger.hpp"
#include "TestHelpers/Logging/TestLogBackend.hpp"

struct DefaultUnitTest {
    TestLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH, 8> testLogBackend;

    DefaultUnitTest() {
        if(LogSingleton::is_valid()) {
            LogSingleton::destroy();
        }
        ELSF_LOG_INIT(testLogBackend);
    }
    ~DefaultUnitTest() {
        if(LogSingleton::is_valid()) {
            LogSingleton::destroy();
        }
    }
};