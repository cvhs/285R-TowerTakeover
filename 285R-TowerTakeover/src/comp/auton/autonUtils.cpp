#include "autonUtils.hpp"

#include "bigZone.hpp"
#include "devices/devices.hpp"
#include "otherAuts.hpp"
#include "smallZone.hpp"

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

  // Check if paths loaded in correctly; if not, generate them and store them to
  // SD card
  if (!pathLoaded("dx=4 dy=0")) {
    // 4 feet (for 3 cube row or 4 cube row)
    profiler->generatePath(
      {{0_ft, 0_ft, 0_deg},
      {8_ft, 0_ft, 0_deg}},
      "dx=4 dy=0"
    );
    profiler->storePath("/usd/paths/", "dx=4 dy=0");
  }

  if (!pathLoaded("dx=4 dy=-2")) {
    // S-curve
    profiler->generatePath({{0_ft, 0_ft, 0_deg}, {4_ft, -2_ft, 0_deg}},
                           "dx=4 dy=-2");
    profiler->storePath("/usd/paths", "dx=4 dy=-2");
  }

  if (!pathLoaded("dx=4 dy=2")) {
    // S-curve
    profiler->generatePath({{0_ft, 0_ft, 0_deg}, {4_ft, 2_ft, 0_deg}},
                           "dx=4 dy=2");
    profiler->storePath("/usd/paths", "dx=4 dy=2");
  }

  if (!pathLoaded("dx=2.5 dy=0")) {
    // 2.5 feet (for reversing after 4 cube row to stack)
    profiler->generatePath({{0_ft, 0_ft, 0_deg}, {3.5_ft, 0_ft, 0_deg}},
                           "dx=2.5 dy=0");
    profiler->storePath("/usd/paths/", "dx=2.5 dy=0");
  }
}

void stack() {
  // Push bottom cube low enough that it touches ground
  // outtakeToStack();
  rollers.moveRelative(-650, 60);
  trayController.state = TrayStates::up;
  while (!trayController.settled) {
    pros::delay(10);
  }
  rollers.moveVelocity(-60);
  pros::delay(400);
  trayController.state = TrayStates::down;
  autChassis->moveDistance(-1_ft);
  rollers.moveVelocity(0);
}

void outtakeToStack() {
  while (lineSensor.get_value_calibrated() > 2000) {
    std::cout << lineSensor.get_value() << std::endl;
    rollers.moveVelocity(-60);
    pros::delay(50);
  }
  rollers.moveVelocity(0);
}

void imuTurn(double degrees) {
  const double kP = 0.03;
  const double kD = 0.135;
  model->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

  double initial = imu.get_heading();
  double final = degrees;

  double sensorVal = initial;
  double target = final;

  double delta = std::abs(final - initial);

  if(delta > 180) {
    if(final > 180) {
      target = final - 360;
    }

    if(initial > 180) {
      sensorVal = initial - 360;
    }
  }

  double error = target - sensorVal;
  double lastError = error;

  bool settled = false;
  std::cout << "Target: " << target << std::endl;
  while(!settled) {
    sensorVal = imu.get_heading();

    if(delta > 180) {
      if(sensorVal > 180) {
        sensorVal -= 360;
      }
    }


    error = target - sensorVal;
    double dError = error - lastError;

    std::cout << "SensorVal: " << sensorVal << std::endl;
    std::cout << "dError: " << dError << std::endl;

    double p = kP * error;
    double d = kD * dError;

    double output = p + d;

    model->rotate(-output);

    lastError = error;
    
    settled = std::abs(error) < 1 && std::abs(dError) < 0.3;

    pros::delay(20);
  }

  model->rotate(0);
}

void deploy() {
  lift.moveAbsolute(420, 100);
  rollers.moveVelocity(-100);
  while (lift.getPosition() < 370) {
    pros::delay(10);
  }

  pros::Task lowerLift([] {
    while (pot.get() < 3900) {
      lift.moveVelocity(-100);
    }
    lift.moveVelocity(0);
  });
  rollers.moveVelocity(0);

  while (pot.get() < 3400) {
    pros::delay(10);
  }
}

int autonSelected = 2;

void autonSelectorFn() {
  pros::lcd::initialize();

  while (true) {
    if (leftSwitch.get_new_press() && autonSelected > 0) {
      autonSelected--;
    } else if (rightSwitch.get_new_press() && autonSelected < 3) {
      autonSelected++;
    }

    switch (autonSelected) {
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
  switch (autonSelected) {
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