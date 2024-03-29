#pragma once

#include "../sml.hpp"
#include "Base.hpp"
#include "CommonEvents.hpp"
#include "Turning.hpp"
#include <iostream>
#include <map>

using namespace boost::sml;

struct EStop;
struct Idle;

Action action;

template <class = class Dummy>
class Turning : public BaseState
{
public:
    struct SetSettingsEvent
    {
        enum class SettingsKey
        {
            Direction = 0,
            RequiresSync,
            DestinationPosition,
            StartPosition,
            FeedRate,
            RapidRate
        };
        std::map<SettingsKey, int32_t> settings;
    };

    // class WaitForUser
    //     : public BaseState // needs 2 sub states, retracting, and unretracting, and waiting
    // { // wait for user needs to unretract when transitioning to wait for sync via NextPassEvent

    // public:
    //     // auto operator()() const noexcept
    //     // {
    //     //     // clang-format off
    //     // return make_transition_table(
    //     //     //WaitForuser
    //     //     *state<Turning<>::WaitForUser::Waiting> +
    //     //     event<Turning<>::WaitForUser::Waiting::ReturnToStartEvent> / action =
    //     //     state<Turning<>>//::ReturnToStart>
    //     //     //,state<Turning<>::WaitForUser::Waiting> +
    //     //     event<Turning<>::WaitForUser::Waiting::NextPassEvent> / action =
    //     //     state<Turning<>::TurningPass>
    //     // );
    //     // }

    //     struct Waiting : public BaseState
    //     {
    //         struct NextPassEvent : public BaseEvent
    //         {
    //         };

    //         struct ReturnToStartEvent : public BaseEvent
    //         {
    //         };

    //         void OnEvent(const NextPassEvent&);
    //         void OnEvent(const ReturnToStartEvent&);
    //     };
    // };

    // class TurningPass : public BaseState
    // {
    // public:

    //     auto operator()() const noexcept
    //     {
    //         // clang-format off
    //         return make_transition_table(
    //             //*state<Turning<>::TurningPass> / action =
    //             state<Turning<>::TurningPass::Unretracting>
    //             *state<Turning<>::TurningPass::Unretracting> + event<MoveDoneEvent> / action =
    //             state<Turning<>::TurningPass::WaitForSync>
    //             ,state<Turning<>::TurningPass::WaitForSync> +
    //             event<Turning<>::TurningPass::WaitForSync::InSyncEvent> / action =
    //             state<Turning<>::TurningPass::Moving> ,state<Turning<>::TurningPass::Moving> +
    //             event<MoveDoneEvent> / action = state<Turning<>::TurningPass::Retracting>
    //             ,state<Turning<>::TurningPass::Retracting> + event<MoveDoneEvent> / action =
    //             state<Turning<>::WaitForUser::Waiting>

    //         );
    //     }

    //     struct Unretracting : public BaseState
    //     {
    //         void OnEvent(const MoveDoneEvent&);
    //     };

    //     struct WaitForSync : public BaseState
    //     {
    //         struct InSyncEvent : public BaseEvent
    //         {
    //         };
    //         void OnEvent(const InSyncEvent&);
    //     };

    //     struct Moving : public BaseState
    //     {
    //         void OnEvent(const MoveDoneEvent&);

    //         void OnEvent(const StopEvent&);
    //     };

    //     struct Retracting : public BaseState
    //     {
    //         void OnEvent(const MoveDoneEvent&);
    //     };

    //     // void OnEvent(const EStopEvent&); //this might be able to bubble up to the parent
    // };

    // class ReturnToStart : public BaseState
    // {
    // public:
    //     auto operator()() const noexcept
    //     {
    //         // clang-format off
    //         return make_transition_table(
    //             *state<Turning<>::ReturnToStart> / action =
    //             state<Turning<>::ReturnToStart::Retracting>
    //             ,state<Turning<>::ReturnToStart::Retracting> + event<MoveDoneEvent> / action =
    //             state<Turning<>::ReturnToStart::MovingToStart>
    //             ,state<Turning<>::ReturnToStart::MovingToStart> + event<MoveDoneEvent> / action =
    //             state<Turning<>::WaitForUser::Waiting>

    //         );
    //     }
    //     struct Retracting : public BaseState
    //     {
    //         void OnEvent(const MoveDoneEvent&);
    //     };

    //     struct MovingToStart : public BaseState
    //     {
    //         void OnEvent(const MoveDoneEvent&); // Transition back to WaitForUser::Waiting
    //     };

    //     void OnEvent(const MoveDoneEvent&);
    // };

    void OnEvent(const ExitEvent&);
    void OnEvent(const EStopEvent&);
    void OnEvent(const SetSettingsEvent&);

    auto operator()() const noexcept
    {

        return make_transition_table(
            // root and inherited actions
            //*state<Turning<>> / action = state<Turning<>::WaitForUser> //::Waiting>
            *state<Turning<>> + event<EStopEvent> / action = state<EStop>
            // ,state<Turning<>> + event<StopEvent> / action =
            // state<Turning<>::WaitForUser::Waiting> ,state<Turning<>> + event<ExitEvent> / action
            // = state<Idle> ,state<Turning<>> + event<Turning<>::SetSettingsEvent> / action =
            // state<Turning<>::WaitForUser::Waiting>

        );
    }
    // clang-format on
public:
    // sm<>* GetCurrentSM() { return &WaitForUserSM; }

private:
    // sm<WaitForUser> WaitForUserSM;
    // sm<TurningPass> TurningPassSM;
    // sm<ReturnToStart> ReturnToStartSM;

    bool myRequiresSync = false; // false for turning modes, true for threading modes
    bool myForwardPass = true;   // true for to take a pass towards the destination, false for
                                 // towards the start. for reversing the cut direction without
                                 // redefining the start and end positions
    int32_t myDestinationPosition = 0;
    int32_t myStartPostion = 0;
    int32_t myFeedRate = 0;  // in distance per spindle rev
    int32_t myRapidRate = 0; // in distance per second
};