#include <gtest/gtest.h>
#include "Logging/Logger.hpp"

class LoggerTest : public testing::Test {
protected:
    void SetUp() override {
        if(LogSingleton::is_valid()) {
            LogSingleton::destroy();
        }
    }

    void TearDown() override {
        if(LogSingleton::is_valid()) {
            LogSingleton::destroy();
        }
    }
};