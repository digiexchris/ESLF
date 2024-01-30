#pragma once
#include <etl/message.h>
#include <etl/utility.h>
#include <cstddef>
#include <algorithm>
#include "Logging/Logger.hpp"
#include "State/Machine/Messages.hpp"
#include "State/Machine/Machine.hpp"

namespace eslf {
namespace test {
    constexpr size_t MaxMessageSize = std::max(
        {
            sizeof(StartMessage), 
            sizeof(StopMessage),
            sizeof(StartAtMessage),
            sizeof(StopAtMessage),
            sizeof(EStopMessage),
            sizeof(ResetMessage)
            });

    struct MessageTestCase {
        MessageWrapper message;
        MachineStateId expectedState;
    };

// RAII Wrapper for Messages
class MessageWrapper {
public:
    template <typename T, typename... Args>
    MessageWrapper(Args&&... args) {
        message = new (messageBuffer) T(std::forward<Args>(args)...);
    }

    ~MessageWrapper() {
        if (message != nullptr) {
            message->~imessage();
        }
    }

    etl::imessage* get() const {
        return message;
    }

private:
    static alignas(std::max_align_t) char messageBuffer[MaxMessageSize];
    etl::imessage* message = nullptr;
};

} // namespace test
} // namespace eslf

