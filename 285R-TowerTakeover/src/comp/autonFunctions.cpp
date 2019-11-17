#include "../devices/devices.hpp"
#include "autonFunctions.hpp"

void red5Cubes() {
  rollers.moveVelocity(160);
  chassis->setState({0.5_ft, 9.75_ft, 0_deg});
  chassis->driveToPoint({4.5_ft, 9.75_ft});
  pros::delay(250);
  rollers.moveVelocity(0);
  chassis->driveToPoint({3.75_ft, 9.75_ft}, true);
  chassis->driveToPoint({1.5_ft, 9.0_ft});
  
  rollers.moveRelative(-850, 100);
  tray.setState(TrayController::trayStates::up);
  while(tray.getState() == TrayController::trayStates::up){}
  tray.setState(TrayController::trayStates::down);
  rollers.moveVelocity(-100);
  pros::delay(200);
  chassis->moveDistance(-1_ft);
  rollers.moveVelocity(0);
}

void blue5Cubes() {
  rollers.moveVelocity(160);
  chassis->setState({11.5_ft, 9.75_ft, 180_deg});
  chassis->driveToPoint({7.5_ft, 9.75_ft});
  pros::delay(250);
  rollers.moveVelocity(0);
  chassis->driveToPoint({8.25_ft, 9.75_ft}, true);
  chassis->driveToPoint({10_ft, 8.15_ft}, false, 0_in);

  rollers.moveRelative(-850, 100);
  tray.setState(TrayController::trayStates::up);
  while(tray.getState() == TrayController::trayStates::up){}
  tray.setState(TrayController::trayStates::down);
  rollers.moveVelocity(-100);
  pros::delay(200);
  chassis->moveDistance(-1_ft);
  rollers.moveVelocity(0);
}