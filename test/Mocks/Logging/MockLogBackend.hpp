#include <gmock/gmock.h>
#include <etl/string.h>
#include <cstdio>
#include <cstdarg> // For va_list, va_start, va_end
#include <string>
#include <Logging/Logger.hpp>

namespace Mocks::Logging {

template <size_t MaxMessageLength>
class MockLogBackend : public ILogBackend<MaxMessageLength>
{
public:
    MOCK_METHOD(void, LogFormattedInfo, (const std::string& message), (const));
    MOCK_METHOD(void, LogFormattedWarn, (const std::string& message), (const));
    MOCK_METHOD(void, LogFormattedError, (const std::string& message), (const));

    // Constructor that accepts a uint32_t argument for uniqueId
    explicit MockLogBackend(uint32_t id = 0) : uniqueId(id) {}

    virtual void Info(etl::string<MaxMessageLength> message, ...) const override {
        va_list args;
        va_start(args, message);
        std::string formatted = FormatString(message.c_str(), args);
        va_end(args);
        LogFormattedInfo(formatted);
    }

    virtual void Warn(etl::string<MaxMessageLength> message, ...) const override {
        va_list args;
        va_start(args, message);
        std::string formatted = FormatString(message.c_str(), args);
        va_end(args);
        LogFormattedWarn(formatted);
    }

    virtual void Error(etl::string<MaxMessageLength> message, ...) const override {
        va_list args;
        va_start(args, message);
        std::string formatted = FormatString(message.c_str(), args);
        va_end(args);
        LogFormattedError(formatted);
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
