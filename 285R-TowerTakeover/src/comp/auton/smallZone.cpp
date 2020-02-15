#include "smallZone.hpp"

#include "autonUtils.hpp"
#include "devices/devices.hpp"

void redSmall5Cube() {
  // Deploy tray and intake
  deploy();

  // Start rollers and intake the 4 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4 dy=0");
  deployAntitips();
  profiler->waitUntilSettled();

  // Stop rollers and move back
  profiler->setTarget("dx=2.5 dy=0", true);
  pros::delay(1000);
  rollers.moveVelocity(0);
  profiler->waitUntilSettled();

  // Turn to goal zone and approach
  // autChassis->setState({0_ft, 0_ft, 0_deg});
  autChassis->turnAngle(-135_deg);
  autChassis->moveDistance(1.5_ft);

  stack();
}

void blueSmall5Cube() {
  // Deploy tray and intake
  deploy();

  // Start rollers and intake the 4 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4 dy=0");
  deployAntitips();
  profiler->waitUntilSettled();

  // Stop rollers and move back
  profiler->setTarget("dx=2.5 dy=0", true);
  pros::delay(1000);
  rollers.moveVelocity(0);
  // outtakeToStack();
  profiler->waitUntilSettled();

  // Turn to goal zone and approach
  autChassis->setState({0_ft, 0_ft, 0_deg});
  autChassis->turnToAngle(125_deg);
  autChassis->moveDistance(1_ft);
  // autChassis->turnAngle(135_deg);
  // autChassis->moveDistance(1_ft);

  stack();
}

void redSmall8Cube() {
  // Deploy tray and intake
  deploy();

  // Start rollers and intake the 3 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4 dy=0");
  profiler->waitUntilSettled();

  // Stop rollers and s-curve back
  rollers.moveVelocity(0);
  profiler->setTarget("dx=4 dy=-2", true);
  profiler->waitUntilSettled();

  // Start rollers and intake 4 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4 dy=-2");
  profiler->waitUntilSettled();

  // Stop rollers and move back
  rollers.moveVelocity(0);
  profiler->setTarget("dx=2.5 dy=0", true);
  profiler->waitUntilSettled();

  // Turn to goal zone and approach
  autChassis->setState({0_ft, 0_ft, 0_deg});
  autChassis->turnToAngle(135_deg);
  autChassis->moveDistance(2_ft);

  stack();
}

void blueSmall8Cube() {
  // Deploy tray and intake
  deploy();

  // Start rollers and intake the 3 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4 dy=0");
  profiler->waitUntilSettled();

  // Stop rollers and s-curve back
  rollers.moveVelocity(0);
  profiler->setTarget("dx=4 dy=-2", true);
  profiler->waitUntilSettled();

  // Start rollers and intake 4 cubes
  rollers.moveVelocity(200);
  profiler->setTarget("dx=4 dy=2");
  profiler->waitUntilSettled();

  // Stop rollers and move back
  rollers.moveVelocity(0);
  profiler->setTarget("dx=2.5 dy=0", true);
  profiler->waitUntilSettled();

  // Turn to goal zone and approach
  autChassis->setState({0_ft, 0_ft, 0_deg});
  autChassis->turnToAngle(225_deg);
  autChassis->moveDistance(2_ft);

  stack();
}