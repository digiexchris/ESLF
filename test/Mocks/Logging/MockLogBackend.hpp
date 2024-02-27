#pragma once

#include <catch2/catch_all.hpp>
#include <catch2/trompeloeil.hpp>
#include <trompeloeil/mock.hpp>
#include <etl/string.h>
#include <cstdio>
#include <cstdarg> // For va_list, va_start, va_end
#include <string>
#include "Logging/Logger.hpp"

namespace Mocks::Logging  {

template <size_t MaxMessageLength>
class MockLogBackend : public ILogBackend<MaxMessageLength>
{
public:
    MAKE_CONST_MOCK1(InfoMock, void (etl::string<MaxMessageLength> message));
    MAKE_CONST_MOCK1(WarnMock, void (etl::string<MaxMessageLength> message));
    MAKE_CONST_MOCK1(ErrorMock, void (etl::string<MaxMessageLength> message));
    // //MAKE_MOCK1(Info, void(const std::string& message));
    // MAKE_MOCK1(Warn, void(const std::string& message));
    // MAKE_MOCK1(Error, void(const std::string& message));

    // Constructor that accepts a uint32_t argument for uniqueId
    explicit MockLogBackend(uint32_t id = 0) : uniqueId(id) {}

    virtual void Info(etl::string<MaxMessageLength> message, ...) const override {
        va_list args;
        va_start(args, message);
        etl::string<MaxMessageLength> formatted = FormatString(message.c_str(), args).c_str();
        va_end(args);
        InfoMock(formatted);
    }

    virtual void Warn(etl::string<MaxMessageLength> message, ...) const override {
        va_list args;
        va_start(args, message);
        etl::string<MaxMessageLength> formatted = FormatString(message.c_str(), args).c_str();
        va_end(args);
        WarnMock(formatted);
    }

    virtual void Error(etl::string<MaxMessageLength> message, ...) const override {
        va_list args;
        va_start(args, message);
        etl::string<MaxMessageLength> formatted = FormatString(message.c_str(), args).c_str();
        va_end(args);
        ErrorMock(formatted);
    }

    uint32_t uniqueId; // Make sure uniqueId is public if you need to access it outside the class

private:
    std::string FormatString(const char* format, va_list args) const {
        char buffer[MaxMessageLength];
        vsnprintf(buffer, sizeof(buffer), format, args);
        return std::string(buffer);
    }
};

} // namespace Mocks::Logging
