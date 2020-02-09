#include "devices/devices.hpp"
#include "otherAuts.hpp"
#include "autonUtils.hpp"

void oneCube() {
  autChassis->moveDistance(-1.5_ft);
  pros::delay(800);
  autChassis->moveDistance(1.5_ft);
}

void twoCube() {
  rollers.moveVelocity(200);
  autChassis->moveDistance(2_ft);
  rollers.moveVelocity(0);
  autChassis->moveDistance(-1_ft);
  autChassis->turnAngle(120_deg);
  rollers.moveVelocity(-100);
  rollers.moveVelocity(0);
  autChassis->moveDistance(-1_ft);
}