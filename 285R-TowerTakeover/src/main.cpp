#include "comp/comp.hpp"
#include "devices/devices.hpp"

void initialize() {
  generatePaths();

  pros::Task trayTask(trayTaskFn);
  pros::Task autonSelectorTask(autonSelectorFn, "autonSelector");
}

void disabled() {}

void competition_initialize() {}

void autonomous() { runAuton(); }

void opcontrol() {
  while (1) {
    driveToggle();

    trayControl();
    liftControl();
    rollerControl();

    rollerBrakeManagement();

    pros::delay(20);
  }
}
