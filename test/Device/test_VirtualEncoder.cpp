#include <catch2/catch_all.hpp>

#include "Device/VirtualEncoder.hpp"
#include "State/Position.hpp"

TEST_CASE("VirtualEncoder")
{
    Device::VirtualEncoder encoder(1.0f);
    encoder.SetCountIncrement(10);
    encoder.SetDirection(true);
    encoder.Update();
    REQUIRE(encoder.GetPosition() == 10);
    REQUIRE(encoder.GetDirection() == true);
    REQUIRE(encoder.GetTimestamp() == 10);
    encoder.SetCountIncrement(20);
    encoder.SetDirection(false);

    encoder.Update();
    REQUIRE(encoder.GetPosition() == -10);
    REQUIRE(encoder.GetDirection() == false);
    REQUIRE(encoder.GetTimestamp() == 20);
}