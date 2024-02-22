#include "State/Position.hpp"

#include <etl/type_traits.h>

namespace Device
{



class IEncoder : public State::Position
{

    protected:
    // Protected constructor to prevent instantiation of IEncoder directly
    IEncoder() = default;
    ~IEncoder() = default; // Ensure proper destruction of derived classes
};


// Traits to check if a type used in a template can be used as an encoder
template<typename T, typename = void>
struct IsEncoder : etl::false_type {};

template<typename T>
struct IsEncoder<T,  etl::void_t<decltype( etl::declval<T>().UpdateMotionParams())>> :  etl::true_type {};

} // namespace Device