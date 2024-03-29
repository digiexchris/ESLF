// $CXX -std=c++14 nested.cpp
#include "Machine/FSM/sml.hpp"
#include <cassert>
#include <catch2/catch_all.hpp>

namespace sml = boost::sml;

namespace
{
template <class = class Dummy> // Use a dummy template to delay POI and support nested SM
class top
{
    struct e1
    {
    };

    struct nested
    {
        auto operator()() const noexcept
        {
            using namespace sml;
            return make_transition_table(*"idle"_s + event<e1> = X);
        }
    };

public:
    void process()
    {
        sm.process_event(e1{});
        assert(sm.is(sml::X));
    }

private:
    sml::sm<nested> sm{};
};
} // namespace

TEST_CASE("SML Nesting tes", "[Machine][FSM][Root]")
{
    top<> sm{};
    sm.process();
}
