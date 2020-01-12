#include "../devices/devices.hpp"
#include "autonFunctions.hpp"

int aut = 3;
void selectAuton() {
  int val = pot.get();
  while(1) {
    val = pot.get();
    aut = val <= 1023 ? 0 : val <= 2047 ? 1 : val <= 3071 ? 2 : 3;
  }
}

void stack() {
  // Push bottom cube low enough that it touches ground
  outtakeToStack();
  rollers.moveRelative(-500, 100);
  rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  // Stack then back up
  tray.setState(TrayController::trayStates::up);
  while(tray.getState() == TrayController::trayStates::up){}
  tray.setState(TrayController::trayStates::down);
  rollers.moveVelocity(-75);
  pros::delay(200);
  autChassis->moveDistance(-1_ft);
  rollers.moveVelocity(0);
}

void outtakeToStack() {
  while(lineSensor.get_value_calibrated() > 2000) {
    std::cout << lineSensor.get_value() << std::endl;
    rollers.moveVelocity(-60);
    pros::delay(50);
  }
  rollers.moveVelocity(0);
}

void deploy() {
  // TODO: actually figure this out
}

void redSmall5Cube() {
  // Asynchronously generate first path
  pros::Task pathgen1([] (void* inp) {
    profiler->generatePath(
      {{0_ft, 0_ft, 0_deg},
       {4_ft, 0_ft, 0_deg}},
      "4 Cubes"
    );
  }, (void*)"inp", TASK_PRIORITY_DEFAULT - 1, 
  TASK_STACK_DEPTH_DEFAULT, "pathgen1");

  // Deploy tray and intake while path is generating
  deploy();

  // Check if path is done generating, if not then wait until it is then kill the task
  std::vector<std::string> paths;
  do {
    paths = profiler->getPaths();
  } while(std::find(paths.begin(), paths.end(), "4 Cubes") != paths.end());
  pathgen1.remove();

  // Start rollers and intake the 4 cubes, generate the next path
  rollers.moveVelocity(200);
  profiler->setTarget("4 Cubes");
  profiler->generatePath(
    {{  0_ft, 0_ft, 0_deg},
     {2.5_ft, 0_ft, 0_deg}},
     "Reverse to turn"
  );
  profiler->waitUntilSettled();
  profiler->removePath("4 Cubes");

  // Stop rollers and move back
  rollers.moveVelocity(0);
  profiler->setTarget("Reverse to turn", true);
  profiler->waitUntilSettled();

  // Turn to goal zone and approach
  autChassis->setState({0_ft, 0_ft, 0_deg});
  autChassis->turnToAngle(135_deg);
  autChassis->moveDistance(2_ft);

  stack();
}

void redSmall8Cube() {
  // Asynchronously generate first path
  pros::Task pathgen1([] (void* inp) {
    profiler->generatePath(
      {{0_ft, 0_ft, 0_deg},
       {4_ft, 0_ft, 0_deg}},
      "3 Cubes"
    );
  }, (void*)"inp", TASK_PRIORITY_DEFAULT - 1, 
  TASK_STACK_DEPTH_DEFAULT, "pathgen1");

  // Deploy tray and intake while path is generating
  deploy();

  // Check if path is done generating, if not then wait until it is then kill the task
  std::vector<std::string> paths;
  do {
    paths = profiler->getPaths();
  } while(std::find(paths.begin(), paths.end(), "3 Cubes") != paths.end());
  pathgen1.remove();

  // Start rollers and intake the 3 cubes, generate the next path
  rollers.moveVelocity(200);
  profiler->setTarget("3 Cubes");
  profiler->generatePath(
    {{  0_ft, 0_ft, 0_deg},
     {4_ft, -2_ft, 0_deg}},
     "Reverse s-curve"
  );
  profiler->waitUntilSettled();
  profiler->removePath("4 Cubes");

  // Stop rollers and s-curve back, generate next path
  rollers.moveVelocity(0);
  profiler->setTarget("Reverse to turn", true);
  profiler->generatePath(
    {{0_ft, 0_ft, 0_deg},
     {4_ft, 0_ft, 0_deg}},
     "4 Cubes"
  );
  profiler->waitUntilSettled();

  // Start rollers and intake 4 cubes, generate next path
  rollers.moveVelocity(200);
  profiler->setTarget("4 Cubes");
  profiler->generatePath(
    {{  0_ft, 0_ft, 0_deg},
     {2.5_ft, 0_ft, 0_deg}},
     "Reverse to turn"
  );
  profiler->waitUntilSettled();
  profiler->removePath("4 Cubes");

  // Stop rollers and move back
  rollers.moveVelocity(0);
  profiler->setTarget("Reverse to turn", true);
  profiler->waitUntilSettled();

  // Turn to goal zone and approach
  autChassis->setState({0_ft, 0_ft, 0_deg});
  autChassis->turnToAngle(135_deg);
  autChassis->moveDistance(2_ft);

  stack();
}

void oneCube() {
  autChassis->moveDistance(-1.5_ft);
  pros::delay(800);
  autChassis->moveDistance(1.5_ft);
  // tray.setState(TrayController::trayStates::up);
  // pros::delay(1000);
  // tray.setState(TrayController::trayStates::down);
}