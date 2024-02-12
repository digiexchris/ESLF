#include <iostream>
#include <cmath>


namespace Postition {

// Constants
const int targetEncoderResolution = 1000; // Resolution of the target encoder
const int motorEncoderResolution = 800;  // Resolution of the motor's encoder
const int motorCommandResolution = 1200; // Resolution for motor position commands
const double updateInterval = 0.01;      // Control loop update interval in seconds

// Global variables to track fractional accumulation for scaling
double fractionalErrorAccumulation = 0.0;

// Function prototypes
int scaleTargetPositionToMotorCommand(double targetEncoderPosition);
void updateMotorPosition(int motorCommandPosition, int& motorActualPosition);

int main() {
    double targetEncoderPosition = 0.0; // Position from the main encoder
    int motorActualPosition = 0;       // Motor's actual position (integer)

    // Simulated target encoder position update (e.g., full revolution)
    targetEncoderPosition = targetEncoderResolution;

    // Control loop (Example with 100 updates)
    for(int i = 0; i < 100; ++i) {
        int motorCommandPosition = scaleTargetPositionToMotorCommand(targetEncoderPosition);
        updateMotorPosition(motorCommandPosition, motorActualPosition);

        // Simulate motor encoder update or control motor here based on motorCommandPosition
        // This example simply outputs the calculated motor command position
        std::cout << "Update " << i << ": Motor Command Position: " << motorCommandPosition << ", Motor Actual Position: " << motorActualPosition << std::endl;
    }

    return 0;
}

int scaleTargetPositionToMotorCommand(double targetEncoderPosition) {
    // Scale target position from target encoder scale to motor command scale
    double scaledPosition = (targetEncoderPosition * motorCommandResolution) / targetEncoderResolution;

    // Add accumulated fractional error to improve accuracy over time
    double newPosition = scaledPosition + fractionalErrorAccumulation;
    int finalPosition = static_cast<int>(round(newPosition)); // Round to nearest integer

    // Update fractionalErrorAccumulation with the new fractional part
    fractionalErrorAccumulation += (newPosition - finalPosition);

    // Correct fractionalErrorAccumulation drift
    if (fabs(fractionalErrorAccumulation) >= 1.0) {
        int correction = static_cast<int>(fractionalErrorAccumulation);
        finalPosition += correction;
        fractionalErrorAccumulation -= correction;
    }

    return finalPosition;
}

void updateMotorPosition(int motorCommandPosition, int& motorActualPosition) {
    // Assuming motorActualPosition is updated based on feedback from the motor's encoder
    // This step would involve converting motorCommandPosition back to motorEncoderResolution, if necessary
    // For simplicity, this example directly sets motorActualPosition to the command position
    // In a real application, you'd read this value from the motor's encoder
    motorActualPosition = motorCommandPosition;
}

} // namespace Postition