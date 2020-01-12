#include "devices/devices.hpp"
#include "autonUtils.hpp"

int aut = 3;
void selectAuton() {
  int val = pot.get();
  while(1) {
    val = pot.get();
    aut = val <= 1023 ? 0 : val <= 2047 ? 1 : val <= 3071 ? 2 : 3;
  }
}

bool pathLoaded(std::string pathID) {
  std::vector<std::string> paths = profiler->getPaths();
  bool loaded = paths.end() != std::find(paths.begin(), paths.end(), pathID);

  return loaded;
}

void generatePaths() {
  // Attempt to load in paths from SD card
  profiler->loadPath("/usd/paths/", "dx=4 dy=0");
  profiler->loadPath("/usd/paths/", "dx=4 dy=-2");
  profiler->loadPath("/usd/paths/", "dx=4 dy=2");
  profiler->loadPath("/usd/paths/", "dx=2.5 dy=0");

  // Check if paths loaded in correctly; if not, generate them and store them to SD card
  if(!pathLoaded("dx=4 dy=0")) {
    // 4 feet (for 3 cube row or 4 cube row)
    profiler->generatePath(
      {{0_ft, 0_ft, 0_deg},
      {4_ft, 0_ft, 0_deg}},
      "dx=4 dy=0"
    );
    profiler->storePath("/usd/paths/", "dx=4 dy=0");
  }

  if(!pathLoaded("dx=4 dy=-2")) {
    // S-curve
    profiler->generatePath(
      {{  0_ft, 0_ft, 0_deg},
      {4_ft, -2_ft, 0_deg}},
      "dx=4 dy=-2"
    );
    profiler->storePath("/usd/paths", "dx=4 dy=-2");
  }

  if(!pathLoaded("dx=4 dy=2")) {
    // S-curve
    profiler->generatePath(
      {{  0_ft, 0_ft, 0_deg},
      {4_ft, 2_ft, 0_deg}},
      "dx=4 dy=2"
    );
    profiler->storePath("/usd/paths", "dx=4 dy=2");
  }

  if(!pathLoaded("dx=2.5 dy=0")) {
    // 2.5 feet (for reversing after 4 cube row to stack)
    profiler->generatePath(
      {{  0_ft, 0_ft, 0_deg},
      {2.5_ft, 0_ft, 0_deg}},
      "dx=2.5 dy=0"
    );
    profiler->storePath("/usd/paths/", "dx=2.5 dy=0");
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