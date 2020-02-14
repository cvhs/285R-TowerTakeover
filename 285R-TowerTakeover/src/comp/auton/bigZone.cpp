#include "devices/devices.hpp"
#include "autonUtils.hpp"
#include "bigZone.hpp"

void redBig3Cube() {
    deploy();
    rollers.moveVelocity(200);
    autChassis->moveDistance(1.9_ft);

    autChassis->turnToAngle(-100_deg);

    autChassis->setMaxVelocity(120);
    autChassis->moveDistance(2.8_ft);
    autChassis->setMaxVelocity(80);
    pros::delay(200);

    autChassis->setMaxVelocity(120);
    autChassis->moveDistanceAsync(-2.9_ft);
    pros::delay(500);
    rollers.moveVelocity(0);
    autChassis->waitUntilSettled();
    autChassis->setMaxVelocity(80);

    autChassis->turnToAngle(-235_deg);

    autChassis->moveDistance(0.5_ft);

    rollers.moveRelative(-2500, 150);
    pros::delay(1000);
    lift.moveRelative(200, 80);
    pros::delay(500);
    rollers.moveRelative(-1000, 100);
    pros::delay(500);

    autChassis->moveDistance(-0.8_ft);

}

void blueBig3Cube() {}