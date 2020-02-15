#include "bigZone.hpp"

#include "autonUtils.hpp"
#include "devices/devices.hpp"

void redBig3Cube() {
  deploy();
  rollers.moveVelocity(200);
  autChassis->moveDistance(1.9_ft);
  autChassis->turnAngle(-100_deg);
  autChassis->setMaxVelocity(120);
  autChassis->moveDistanceAsync(2.8_ft);
  deployAntitips();
  autChassis->waitUntilSettled();
  autChassis->setMaxVelocity(80);
  pros::delay(200);
  autChassis->setMaxVelocity(120);
  autChassis->moveDistanceAsync(-2.8_ft);
  pros::delay(500);
  rollers.moveVelocity(0);
  autChassis->waitUntilSettled();
  autChassis->setMaxVelocity(80);
  autChassis->turnAngle(-130_deg);
  autChassis->moveDistance(0.5_ft);

  rollers.moveRelative(-2500, 150);
  pros::delay(1000);
  lift.moveRelative(300, 80);
  pros::delay(500);
  rollers.moveRelative(-1000, 150);
}

void blueBig3Cube() {}