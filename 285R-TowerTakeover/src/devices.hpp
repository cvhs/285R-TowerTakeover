#include "main.h"

extern ChassisScales scales;
extern std::shared_ptr<okapi::OdomChassisController> chassis;
extern std::shared_ptr<okapi::ChassisModel> model;

extern okapi::MotorGroup rollers;
extern okapi::Motor tilt;
extern okapi::Motor arm;

enum trayStates
{
  up,
  down
};

extern trayStates trayState;

// void IntakeController::taskFnc(void* input)
// {
//   pros::delay(500);
//   IntakeController* that = static_cast<IntakeController*>(input);
//   that->run();
// }
