#include "Message.hpp"

namespace eslf {
namespace test {
    
alignas(std::max_align_t) char MessageWrapper::messageBuffer[MaxMessageSize];

} // namespace test
} // namespace eslf