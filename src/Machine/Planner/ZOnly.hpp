#pragma once
#include "Planner.hpp"

namespace Machine
{
namespace Planner
{
template <typename MainSpindleEncoder, typename ZAxisMotor>
class ZOnly : public Planner<MainSpindleEncoder>
{
    public:
        ZOnly(
            MainSpindleEncoder& aMainSpindle, 
            Device::Axis<ZAxisMotor>& anAxis);

        void Update() override;
        void GenerateMoves() override;

    protected:

        void GenerateThreadingMoves();
        void GenerateTurningMoves();

        Device::Axis<ZAxisMotor>& myZAxis;
};

}} // namespace Machine::Planner