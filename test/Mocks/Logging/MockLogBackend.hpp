#pragma once

#include <catch2/catch_all.hpp>
#include <catch2/trompeloeil.hpp>
#include <trompeloeil/mock.hpp>
#include <etl/string.h>
#include <cstdio>
#include <cstdarg> // For va_list, va_start, va_end
#include <string>
#include "Logging/Logger.hpp"
#include <fmt/core.h>

namespace Mocks::Logging  {

class MockLogBackend : public ILogBackend<MockLogBackend>
{
public:
    MAKE_CONST_MOCK1(InfoMock, void (etl::string<256> message));
    MAKE_CONST_MOCK1(WarnMock, void (etl::string<256> message));
    MAKE_CONST_MOCK1(ErrorMock, void (etl::string<256> message));
    // //MAKE_MOCK1(Info, void(const std::string& message));
    // MAKE_MOCK1(Warn, void(const std::string& message));
    // MAKE_MOCK1(Error, void(const std::string& message));

    // Constructor that accepts a uint32_t argument for uniqueId
    explicit MockLogBackend(uint32_t id = 0) : uniqueId(id) {}

    template <typename... Args>
    void Info(etl::string<256> message, Args &&...args) const {
        etl::string<256> formatted = fmt::format(message.c_str(), etl::forward<Args>(args)...).c_str();
        InfoMock(formatted);
    }

    template <typename... Args>
    void Warn(etl::string<256> message, Args &&...args) const {
        etl::string<256> formatted = fmt::format(message.c_str(), etl::forward<Args>(args)...).c_str();
        WarnMock(formatted);
    }

    template <typename... Args>
    void Error(etl::string<256> message, Args &&...args) const {
        etl::string<256> formatted = fmt::format(message.c_str(), etl::forward<Args>(args)...).c_str();
        ErrorMock(formatted);
    }

    uint32_t uniqueId; // Make sure uniqueId is public if you need to access it outside the class

private:
};

} // namespace Mocks::Logging
