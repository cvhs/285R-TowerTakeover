#include "../devices/devices.hpp"
#include "autonFunctions.hpp"

void stack() {
  // Push bottom cube low enough that it touches ground
  // TODO: make this more consistent, maybe with sensor?
  rollers.moveRelative(-850, 100);

  // Stack then back up
  tray.setState(TrayController::trayStates::up);
  while(tray.getState() == TrayController::trayStates::up){}
  tray.setState(TrayController::trayStates::down);
  rollers.moveVelocity(-100);
  pros::delay(200);
  chassis->moveDistance(-1_ft);
  rollers.moveVelocity(0);
}

void red5Cubes() {
  // Turn on rollers
  rollers.moveVelocity(160);

  // Pick up 4 cubes in front
  chassis->setState({0.5_ft, 9.75_ft, 0_deg});
  chassis->driveToPoint({4.5_ft, 9.75_ft});

  // Wait 250ms and stop rollers
  // TODO: see if this can be removed
  pros::delay(250);
  rollers.moveVelocity(0);

  // Back up slightly then turn around and drive to small zone
  chassis->driveToPoint({3.75_ft, 9.75_ft}, true);
  chassis->driveToPoint({1.5_ft, 9.0_ft});
  
  stack();
}

void blue5Cubes() {
  // Turn on rollers
  rollers.moveVelocity(160);
  
  // Pick up 4 cubes in front
  chassis->setState({11.5_ft, 9.75_ft, 180_deg});
  chassis->driveToPoint({7.5_ft, 9.75_ft});

  // Wait 250ms and stop rollers
  // TODO: see if this can be removed
  pros::delay(250);
  rollers.moveVelocity(0);

  // Back up slightly then turn around and drive to small zone
  chassis->driveToPoint({8.25_ft, 9.75_ft}, true);
  chassis->driveToPoint({10_ft, 8.15_ft}, false, 0_in);

  stack();
}

// TODO: test the Cartesian functions
void red5CubesCartesian() {
  // Set Cartesian StateMode
  chassis->setDefaultStateMode(okapi::StateMode::CARTESIAN);

  // Set start position
  chassis->setState({0.5_ft, 2.25_ft, 270_deg});

  // Start rollers and drive forward to gather 4 cubes then stop rollers
  rollers.moveVelocity(160);
  chassis->driveToPoint({4.5_ft, 2.25_ft});
  rollers.moveVelocity(0);

  // Reverse a little bit
  chassis->driveToPoint({2.25_ft, 2.25_ft}, true);

  // Turn to face and drive to small zone
  // TODO: tune the offset distance
  chassis->driveToPoint({0_ft, 0_ft}, false, 1.8_ft);

  // Stack
  stack();
}

void blue5CubesCartesian() {
  // Set Cartesian StateMode
  chassis->setDefaultStateMode(okapi::StateMode::CARTESIAN);

  // Set start position
  chassis->setState({11.5_ft, 2.25_ft, 90_deg});

  // Start rollers and drive forward to gather 4 cubes
  rollers.moveVelocity(160);
  chassis->driveToPoint({7.5_ft, 2.25_ft});
  rollers.moveVelocity(0);

  // Reverse a little bit
  chassis->driveToPoint({9.75_ft, 2.25_ft}, true);

  // Turn to face and drive to small zone
  // TODO: tune the offset distance (should be same as for red)
  chassis->driveToPoint({12_ft, 0_ft}, false, 1.8_ft);

  // Stack
  stack();
}