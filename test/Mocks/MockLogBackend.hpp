#include <gmock/gmock.h>
#include <etl/string.h>
#include <random>

template <size_t MaxMessageLength>
class MockLogBackend : public ILogBackend<MaxMessageLength>
{
public:

    virtual ~MockLogBackend() override {};
    MockLogBackend() = default;
    MockLogBackend(uint32_t uniqueId) : uniqueId(uniqueId) {}
    virtual void Info(etl::string<MaxMessageLength> message, ...) override
    {
        //Info(message, nullptr);
    }
    virtual void Warn(etl::string<MaxMessageLength> message, ...) override
    {
        //Warn(message, nullptr);
    }
    virtual void Error(etl::string<MaxMessageLength> message, ...) override
    {
        //Error(message, nullptr);
    }
    MOCK_METHOD(void, Info, (etl::string<MaxMessageLength> message), ());
    MOCK_METHOD(void, Warn, (etl::string<MaxMessageLength> message), ());
    MOCK_METHOD(void, Error, (etl::string<MaxMessageLength> message), ());
    uint32_t uniqueId;
};
