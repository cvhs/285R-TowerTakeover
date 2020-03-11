#include "bigZone.hpp"

#include "autonUtils.hpp"
#include "devices/devices.hpp"

void redBig3Cube() {
  // Deploy the tray
  deploy();

  // Start rollers and move forward to grab cube in front
  rollers.moveVelocity(200);
  autChassis->moveDistance(1.9_ft);

  autChassis->turnAngle(95_deg);
  autChassis->moveDistance(2.1_ft);

  autChassis->turnAngle(60_deg); // 5124757399
  autChassis->moveDistance(6_in);
  stack();

  // // Turn to face closest mid tower and collect cubes, deploy antitips along the
  // // way
  // autChassis->turnAngle(-100_deg);
  // autChassis->setMaxVelocity(120);
  // autChassis->moveDistanceAsync(2.8_ft);
  // deployAntitips();
  // autChassis->waitUntilSettled();
  // pros::delay(200);

  // // Go back and stop rollers along the way
  // autChassis->moveDistanceAsync(-2.8_ft);
  // pros::delay(500);
  // rollers.moveVelocity(0);
  // autChassis->waitUntilSettled();

  // // Turn to face goal zone and approach it
  // autChassis->setMaxVelocity(80);
  // autChassis->turnAngle(-130_deg);
  // autChassis->moveDistance(0.5_ft);

  // // Spit two cubes into zone, raise lift and spit one on top
  // rollers.moveRelative(-2500, 150);
  // pros::delay(1000);
  // lift.moveRelative(300, 80);
  // pros::delay(500);
  // rollers.moveRelative(-1000, 150);
}

void blueBig3Cube() {
  deploy();
  autChassis->setMaxVelocity(70);

  // Start rollers and move forward to grab cube in front
  rollers.moveVelocity(200);
  autChassis->moveDistance(1.9_ft);

  autChassis->turnAngle(-95_deg);
  autChassis->moveDistance(2.3_ft);

  autChassis->turnAngle(-60_deg);
  autChassis->moveDistance(6_in);
  stack();

  // rollers.moveRelative(-2500, 120);
  // pros::delay(1000);
  // lift.moveRelative(250, 60);
  // pros::delay(500);
  // rollers.moveRelative(-1000, 60);
}
// void blueBig3Cube() {
//   // Deploy the tray
//   deploy();

//   // Start rollers and move forward to grab cube in front
//   rollers.moveVelocity(200);
//   autChassis->moveDistance(1.9_ft);

//   // Turn to face closest mid tower and collect cubes, deploy antitips along the
//   // way
//   autChassis->turnAngle(100_deg);
//   autChassis->setMaxVelocity(120);
//   autChassis->moveDistanceAsync(2.8_ft);
//   deployAntitips();
//   autChassis->waitUntilSettled();
//   pros::delay(200);

//   // Go back and stop rollers along the way
//   autChassis->moveDistanceAsync(-2.8_ft);
//   pros::delay(500);
//   rollers.moveVelocity(0);
//   autChassis->waitUntilSettled();

//   // Turn to face goal zone and approach it
//   autChassis->setMaxVelocity(80);
//   autChassis->turnAngle(130_deg);
//   autChassis->moveDistance(0.5_ft);

//   // Spit two cubes into zone, raise lift and spit one on top
//   rollers.moveRelative(-2500, 150);
//   pros::delay(1000);
//   lift.moveRelative(300, 80);
//   pros::delay(500);
//   rollers.moveRelative(-1000, 150);
// }