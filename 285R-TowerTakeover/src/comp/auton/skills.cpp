#include "skills.hpp"
#include "autonUtils.hpp"
#include "devices/devices.hpp"

void tenCubes() {
    deploy();
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    profiler->generatePath(
        {{0_ft, 0_ft, 0_deg},
         {23_ft, 0_ft, 0_deg}},
         "Ten Cubes"
    );

    rollers.moveVelocity(200);
    profiler->setTarget("Ten Cubes");
    trayController.state = TrayStates::slightlyUp;
    while(!trayController.settled) {
        pros::delay(10);
    }
    trayController.state = TrayStates::down;
    while(!trayController.settled) {
        pros::delay(10);
    }
    profiler->waitUntilSettled();
    pros::delay(2000);
    rollers.moveVelocity(0);

    autChassis->turnToAngle(-45_deg);
    autChassis->moveDistance(1.5_ft);

    stackLots();
}

void stackLots() {
    model->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    trayController.state = TrayStates::up;
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    pros::delay(3000);
    rollers.moveVelocity(-60);
    pros::delay(400);
    trayController.state = TrayStates::down;
    autChassis->moveDistance(-1_ft);
    rollers.moveVelocity(0);
}