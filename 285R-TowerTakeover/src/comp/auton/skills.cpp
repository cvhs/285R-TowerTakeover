#include "skills.hpp"

#include "autonUtils.hpp"
#include "devices/devices.hpp"

void tenCubes() {
  // Deploy tray, set rollers to hold, generate path for motion profiling
  deploy();
  rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  profiler->generatePath({{0_ft, 0_ft, 0_deg}, {23_ft, 0_ft, 0_deg}},
                         "Ten Cubes");

  // Start rollers and drive straight to collect ten cubes and deploy antitips
  // along the way, then wait 2 seconds and stop rollers. Wait is necessary to
  // ensure all cubes fully intaken.
  rollers.moveVelocity(200);
  profiler->setTarget("Ten Cubes");
  deployAntitips();
  profiler->waitUntilSettled();
  pros::delay(2000);
  rollers.moveVelocity(0);

  // Turn to face small goal zone and approach
  autChassis->turnToAngle(-45_deg);
  autChassis->moveDistance(1.5_ft);

  stackLots();
}

void stackLots() {
  model->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
  trayController.state = TrayStates::up;
  rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  pros::delay(3000);
  rollers.moveVelocity(-60);
  pros::delay(400);
  trayController.state = TrayStates::down;
  autChassis->moveDistance(-1_ft);
  rollers.moveVelocity(0);
}