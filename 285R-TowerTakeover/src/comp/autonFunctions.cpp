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

void stack() {
  // // Push bottom cube low enough that it touches ground
  // outtakeToStack();
  // rollers.moveRelative(-500, 100);
  // rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  // // Stack then back up
  // tray.setState(TrayController::trayStates::up);
  // while(tray.getState() == TrayController::trayStates::up){}
  // tray.setState(TrayController::trayStates::down);
  // rollers.moveVelocity(-75);
  // pros::delay(200);
  // autChassis->moveDistance(-1_ft);
  // rollers.moveVelocity(0);
}

void outtakeToStack() {
  // while(lineSensor.get_value_calibrated() > 2000) {
  //   std::cout << lineSensor.get_value() << std::endl;
  //   rollers.moveVelocity(-60);
  //   pros::delay(50);
  // }
  // rollers.moveVelocity(0);
}

void red5CubesCartesian() {
  // // Set Cartesian StateMode
  // autChassis->setDefaultStateMode(okapi::StateMode::CARTESIAN);

  // // Set start position
  // autChassis->setState({0.5_ft, 2.25_ft, 90_deg});

  // // Start rollers and drive forward to gather 4 cubes then stop rollers
  // rollers.moveVelocity(180);
  // autChassis->driveToPoint({4.1_ft, 2.25_ft});
  // pros::delay(300);
  // rollers.moveVelocity(100);

  // // Reverse a little bit
  // autChassis->driveToPoint({2.25_ft, 2.25_ft}, true);
  // rollers.moveVelocity(0);

  // // autChassis->turnAngle(-135_deg);
  // // Turn to face and drive to small zone
  // autChassis->driveToPoint({0_ft, 4.5_ft}, false, 2.1_ft);

  // // Stack
  // stack();
}

void blue5CubesCartesian() {
  // // Set Cartesian StateMode
  // autChassis->setDefaultStateMode(okapi::StateMode::CARTESIAN);

  // // Set start position
  // autChassis->setState({0.5_ft, 2.25_ft, 90_deg});

  // // Start rollers and drive forward to gather 4 cubes
  // rollers.moveVelocity(180);
  // autChassis->driveToPoint({4.1_ft, 2.25_ft});
  // rollers.moveVelocity(100);

  // // Reverse a little bit
  // autChassis->driveToPoint({2.25_ft, 2.25_ft}, true);
  // rollers.moveVelocity(0);

  // // Turn to face and drive to small zone
  // autChassis->driveToPoint({0_ft, 0_ft}, false, 2.1_ft);

  // // Stack
  // stack();
}

void oneCube() {
  // autChassis->moveDistance(-1.5_ft);
  // pros::delay(800);
  // autChassis->moveDistance(1.5_ft);
  // // tray.setState(TrayController::trayStates::up);
  // // pros::delay(1000);
  // // tray.setState(TrayController::trayStates::down);
}