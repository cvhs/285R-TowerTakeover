#include "skills.hpp"

#include "autonUtils.hpp"
#include "devices/devices.hpp"

void tenCubes() {
  deploy();
  rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

  profiler->generatePath({{0_ft, 0_ft, 0_deg}, {23_ft, 0_ft, 0_deg}},
                         "Ten Cubes");

  rollers.moveVelocity(200);
  profiler->setTarget("Ten Cubes");
  deployAntitips();
  profiler->waitUntilSettled();
  pros::delay(2000);
  rollers.moveVelocity(0);

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

void towerLow() {
  lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  while (pot.get() > 2700) {
    lift.moveVelocity(60);
    pros::delay(10);
  }
  lift.moveVelocity(0);
  autChassis->setMaxVelocity(60);
  autChassis->moveDistance(0.4_ft);
  rollers.moveRelative(-1200, 150);
  while (!rollers.isStopped()) {
    lift.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    lift.moveVelocity(0);
    pros::delay(10);
  }
  autChassis->moveDistance(-0.4_ft);
  while (pot.get() < 3400) {
    lift.moveVelocity(-40);
    pros::delay(10);
  }
  lift.moveVoltage(0);
}