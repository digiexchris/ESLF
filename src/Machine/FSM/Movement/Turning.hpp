#pragma once

#include "../sml.hpp"
#include "CommonEvents.hpp"
#include <iostream>
namespace sml = boost::sml;

struct EStop;

struct Turning
{

    bool myRequiresSync = false; // false for turning modes, true for threading modes
    bool myForwardPass = true;   // true for to take a pass towards the destination, false for
                                 // towards the start. for reversing the cut direction without
                                 // redefining the start and end positions
    int32_t myDestinationPosition = 0;
    int32_t myStartPostion = 0;
    int32_t myFeedRate = 0;  // in distance per spindle rev
    int32_t myRapidRate = 0; // in distance per second

    struct ReturnToStartEvent
    {
    };

    struct NextPassEvent
    {
    };

    struct MovingDoneEvent
    {
    };

    struct StopEvent // this needs to stop all movement in the state that handles it. Perhaps
                     // retract if configured?
    {
    };

    struct RetractEvent
    {
    };

    struct SetDirectionEvent
    {
        bool forward = true; // Towards the destination. false is towards the start. ie. this
                             // reverses it so you don't have to re-define the start and end
                             // positions to reverse the cut direction
    };

    struct SetRequiresSyncEvent
    {
        bool requiresSync = false; // wait for the spindle position that re-aligns a thread, or not.
    };

    struct SetDestinationPositionEvent
    {
        int32_t destinationPosition = 0;
    };

    struct SetStartPositionEvent
    {
        int32_t startPostion = 0;
    };

    struct SetFeedRateEvent
    {
        int32_t feedRate = 0; // in distance per spindle rev
    };

    struct SetRapidRateEvent
    {
        int32_t rapidRate = 0; // in distance per second
    };

    auto operator()() const noexcept
    {
        using namespace sml;
        // clang-format off
            return make_transition_table(
            *state<WaitForUser> + event<ReturnToStartEvent> / [] { std::cout << "in sub sm" << std::endl; } = state<ReturnToStart>
            , state<WaitForUser> + event<NextPassEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForSync>
            , state<WaitForSync> + event<WaitForSync::InSyncEvent> / [] { std::cout << "in sub sm" << std::endl; } = state<MovingToDestination>
            , state<MovingToDestination> + event<MovingDoneEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<Retracting>
            , state<Retracting> + event<MovingDoneEvent> / [] { std::cout << "in sub sm, maybe set the target positions here?" << std::endl; } = state<WaitForUser>
            , state<ReturnToStart> + event<RetractEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<MovingToStart>
            , state<MovingToStart> + event<MovingDoneEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<Unretracting>
            , state<Unretracting> + event<MovingDoneEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>

            //Settings
            , state<WaitForUser> + event<SetDirectionEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>
            , state<WaitForUser> + event<SetRequiresSyncEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>
            , state<WaitForUser> + event<SetDestinationPositionEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>
            , state<WaitForUser> + event<SetStartPositionEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>
            , state<WaitForUser> + event<SetFeedRateEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>
            , state<WaitForUser> + event<SetRapidRateEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>

            //user stops it
            , state<WaitForSync> + event<StopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>
            , state<MovingToDestination> + event<StopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>
            , state<MovingToStart> + event<StopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<WaitForUser>

            //estops
            , state<WaitForUser> + event<EStopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<EStop>
            , state<WaitForSync> + event<EStopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<EStop>
            , state<MovingToDestination> + event<EStopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<EStop>
            , state<MovingToStart> + event<EStopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<EStop>
            , state<Retracting> + event<EStopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<EStop>
            , state<Unretracting> + event<EStopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<EStop>
            , state<ReturnToStart> + event<EStopEvent> / [] { std::cout << "finish sub sm" << std::endl; } = state<EStop>
            );
        // clang-format on
    }

    // child states
    struct WaitForUser
    {
    };

    struct MovingToDestination
    {
    };

    struct MovingToStart
    {
    };

    struct WaitForSync
    {
        struct InSyncEvent
        {
        };
    };

    struct Retracting
    {
    };

    struct Unretracting
    {
    };

    struct ReturnToStart
    {
    };
};
