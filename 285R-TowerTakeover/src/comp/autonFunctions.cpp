#include "../devices/devices.hpp"
#include "autonFunctions.hpp"

void stack() {
  // Push bottom cube low enough that it touches ground
  outtakeToStack();
  rollers.moveRelative(-550, 100);
  rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  // Stack then back up
  tray.setState(TrayController::trayStates::up);
  while(tray.getState() == TrayController::trayStates::up){}
  tray.setState(TrayController::trayStates::down);
  rollers.moveVelocity(-70);
  pros::delay(200);
  autChassis->moveDistance(-1_ft);
  rollers.moveVelocity(0);
}

// TODO: tune the  outtake speed
void outtakeToStack() {
  while(lineSensor.get_value_calibrated() > 2000) {
    std::cout << lineSensor.get_value() << std::endl;
    rollers.moveVelocity(-60);
    pros::delay(50);
  }
  rollers.moveVelocity(0);
}

void red5Cubes() {
  // Turn on rollers
  rollers.moveVelocity(160);

  // Pick up 4 cubes in front
  autChassis->setState({0.5_ft, 9.75_ft, 0_deg});
  autChassis->driveToPoint({4.5_ft, 9.75_ft});

  // Wait 250ms and stop rollers
  // TODO: see if this can be removed
  pros::delay(250);
  rollers.moveVelocity(0);

  // Back up slightly then turn around and drive to small zone
  autChassis->driveToPoint({3.75_ft, 9.75_ft}, true);
  autChassis->driveToPoint({1.5_ft, 9.0_ft});
  
  stack();
}

void blue5Cubes() {
  // Turn on rollers
  rollers.moveVelocity(160);
  
  // Pick up 4 cubes in front
  autChassis->setState({11.5_ft, 9.75_ft, 180_deg});
  autChassis->driveToPoint({7.5_ft, 9.75_ft});

  // Wait 250ms and stop rollers
  // TODO: see if this can be removed
  pros::delay(250);
  rollers.moveVelocity(0);

  // Back up slightly then turn around and drive to small zone
  autChassis->driveToPoint({8.25_ft, 9.75_ft}, true);
  autChassis->driveToPoint({10_ft, 8.15_ft}, false, 0_in);

  stack();
}

// TODO: test the Cartesian functions
void red5CubesCartesian() {
  // Set Cartesian StateMode
  autChassis->setDefaultStateMode(okapi::StateMode::CARTESIAN);

  // Set start position
  autChassis->setState({0.5_ft, 2.25_ft, 90_deg});

  // Start rollers and drive forward to gather 4 cubes then stop rollers
  rollers.moveVelocity(140);
  autChassis->driveToPoint({4.75_ft, 2.25_ft});
  pros::delay(300);
  rollers.moveVelocity(0);

  // Reverse a little bit
  autChassis->driveToPoint({2.25_ft, 2.25_ft}, true);

  // autChassis->turnAngle(-135_deg);
  // Turn to face and drive to small zone
  // TODO: tune the offset distance
  autChassis->driveToPoint({0_ft, 4.5_ft}, false, 2.1_ft);

  // Stack
  stack();
}

void blue5CubesCartesian() {
  // Set Cartesian StateMode
  autChassis->setDefaultStateMode(okapi::StateMode::CARTESIAN);

  // Set start position
  autChassis->setState({11.5_ft, 2.25_ft, 90_deg});

  // Start rollers and drive forward to gather 4 cubes
  rollers.moveVelocity(160);
  autChassis->driveToPoint({7.5_ft, 2.25_ft});
  rollers.moveVelocity(0);

  // Reverse a little bit
  autChassis->driveToPoint({9.75_ft, 2.25_ft}, true);

  // Turn to face and drive to small zone
  // TODO: tune the offset distance (should be same as for red)
  autChassis->driveToPoint({12_ft, 0_ft}, false, 1.8_ft);

  // Stack
  stack();
}