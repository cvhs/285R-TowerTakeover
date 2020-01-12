#include "devices/devices.hpp"
#include "otherAuts.hpp"
#include "autonUtils.hpp"

void oneCube() {
  autChassis->moveDistance(-1.5_ft);
  pros::delay(800);
  autChassis->moveDistance(1.5_ft);
  // tray.setState(TrayController::trayStates::up);
  // pros::delay(1000);
  // tray.setState(TrayController::trayStates::down);
}