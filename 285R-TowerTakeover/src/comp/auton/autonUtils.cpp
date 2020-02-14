#include "devices/devices.hpp"
#include "autonUtils.hpp"
#include "smallZone.hpp"
#include "bigZone.hpp"
#include "otherAuts.hpp"

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
      {6.5_ft, 0_ft, 0_deg}},
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
      {3.5_ft, 0_ft, 0_deg}},
      "dx=2.5 dy=0"
    );
    profiler->storePath("/usd/paths/", "dx=2.5 dy=0");
  }
}

void stack() {
  // Push bottom cube low enough that it touches ground
  // outtakeToStack();
  rollers.moveRelative(-300, 60);
  trayController.state = TrayStates::up;
  while(!trayController.settled) {
    pros::delay(10);
  }
  rollers.moveVelocity(-60);
  pros::delay(200);
  trayController.state = TrayStates::down;
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

void rotateIMU(double angle) {
  const double kP = 0.15;              // TUNE
  const double kD = 0;
  double target = imu.get_yaw() + angle;
  bool settled = false;
  double error = angle;
  double lastError = error;

  while(!settled) {
    error = std::fmod(target - imu.get_yaw(), 360);
    double dError = error - lastError;

    double output = kP * error + kD * dError;
    model->rotate(output);
    std::cout << error << "; " << output << "\n";

    settled = std::abs(error) < 1 && dError < 3;
  }

  autChassis->stop();
}

void deploy() {
  // TODO: actually figure this out
  lift.moveAbsolute(420, 100);
  rollers.moveVelocity(-100);
  while(lift.getPosition() < 370) {
    pros::delay(10);
  }

  pros::Task lowerLift([] {
    while(pot.get() < 3900) {
      lift.moveVelocity(-100);
    }
    lift.moveVelocity(0);
  });
  rollers.moveVelocity(0);
  
  while(pot.get() < 3400) {
    pros::delay(10);
  }

  // rollers.moveVelocity(200);
  // pros::delay
}

int autonSelected = 4;

void autonSelectorFn() {
  pros::lcd::initialize();

  while(true) {
    if(leftSwitch.get_new_press() && autonSelected > 0) {
      autonSelected--;
    } else if(rightSwitch.get_new_press() && autonSelected < 3) {
      autonSelected++;
    }

    switch(autonSelected) {
      case 0:
      pros::lcd::print(7, "NO AUTON");
      break;

      case 1:
      pros::lcd::print(7, "One Cube");
      break;

      case 2:
      pros::lcd::print(7, "RED SMALL 5 Cube");
      break;

      case 3:
      pros::lcd::print(7, "BLUE SMALL 5 Cube");
      break;

      case 4:
      pros::lcd::print(7, "RED BIG 3 Cube");
      break;

      case 5:
      pros::lcd::print(7, "BLUE BIG 3 Cube");
      break;

      default:
      pros::lcd::print(7, "INVALID AUTON");
      break;
    }
    pros::delay(20);
  }
}

void runAuton() {
  switch(autonSelected) {
    case 0:
    break;

    case 1:
    oneCube();
    break;

    case 2:
    redSmall5Cube();
    break;

    case 3:
    blueSmall5Cube();
    break;

    case 4:
    redBig3Cube();
    break;

    case 5:
    blueBig3Cube();
    break;

    default:
    break;
  }
}