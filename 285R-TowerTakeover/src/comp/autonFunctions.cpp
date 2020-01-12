#include "../devices/devices.hpp"
#include "autonFunctions.hpp"

int aut = 3;
void selectAuton() {
  int val = pot.get();
  while(1) {
    val = pot.get();
    aut = val <= 1023 ? 0 : val <= 2047 ? 1 : val <= 3071 ? 2 : 3;
  }
}

void generatePaths() {
  // 4 feet (for 3 cube row or 4 cube row)
  profiler->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {4_ft, 0_ft, 0_deg}},
    "dx=4, dy=0"
  );

  // S-curve
  profiler->generatePath(
    {{  0_ft, 0_ft, 0_deg},
     {4_ft, -2_ft, 0_deg}},
     "dx=4, dy=-2"
  );

  // 2.5 feet (for reversing after 4 cube row to stack)
  profiler->generatePath(
    {{  0_ft, 0_ft, 0_deg},
     {2.5_ft, 0_ft, 0_deg}},
     "dx=2.5, dy=2"
  );
}

void stack() {
  // Push bottom cube low enough that it touches ground
  outtakeToStack();
  rollers.moveRelative(-500, 100);
  rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  // Stack then back up
  tray.setState(TrayController::trayStates::up);
  while(tray.getState() == TrayController::trayStates::up){}
  tray.setState(TrayController::trayStates::down);
  rollers.moveVelocity(-75);
  pros::delay(200);
  autChassis->moveDistance(-1_ft);
  rollers.moveVelocity(0);
}

void outtakeToStack() {
  while(lineSensor.get_value_calibrated() > 2000) {
    std::cout << lineSensor.get_value() << std::endl;
    rollers.moveVelocity(-60);
    pros::delay(50);
  }
  rollers.moveVelocity(0);
}

void deploy() {
  // TODO: actually figure this out
}

void redSmall5Cube() {
  // Deploy tray and intake
  deploy();

  // Start rollers and intake the 4 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4, dy=0");
  profiler->waitUntilSettled();

  // Stop rollers and move back
  rollers.moveVelocity(0);
  profiler->setTarget("dx=2.5, dy=0", true);
  profiler->waitUntilSettled();

  // Turn to goal zone and approach
  autChassis->setState({0_ft, 0_ft, 0_deg});
  autChassis->turnToAngle(135_deg);
  autChassis->moveDistance(2_ft);

  stack();
}

void redSmall8Cube() {
  // Deploy tray and intake
  deploy();

  // Start rollers and intake the 3 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4, dy=0");
  profiler->waitUntilSettled();

  // Stop rollers and s-curve back
  rollers.moveVelocity(0);
  profiler->setTarget("dx=4, dy=-2", true);
  profiler->waitUntilSettled();

  // Start rollers and intake 4 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4, dy=-2");
  profiler->waitUntilSettled();

  // Stop rollers and move back
  rollers.moveVelocity(0);
  profiler->setTarget("dx=2.5, dy=0", true);
  profiler->waitUntilSettled();

  // Turn to goal zone and approach
  autChassis->setState({0_ft, 0_ft, 0_deg});
  autChassis->turnToAngle(135_deg);
  autChassis->moveDistance(2_ft);

  stack();
}

void oneCube() {
  autChassis->moveDistance(-1.5_ft);
  pros::delay(800);
  autChassis->moveDistance(1.5_ft);
  // tray.setState(TrayController::trayStates::up);
  // pros::delay(1000);
  // tray.setState(TrayController::trayStates::down);
}