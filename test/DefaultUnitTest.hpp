#pragma once
#include <gtest/gtest.h>
#include "Logging/Logger.hpp"
#include "TestHelpers/Logging/TestLogBackend.hpp"

class DefaultUnitTest : public ::testing::Test {
protected:
    TestLogBackend<ELSF_LOG_MAX_MESSAGE_LENGTH, 8> testLogBackend;
    void SetUp() override {
        if(LogSingleton::is_valid())
        {
            LogSingleton::destroy();
        }

        ELSF_LOG_INIT(testLogBackend);
    }
};