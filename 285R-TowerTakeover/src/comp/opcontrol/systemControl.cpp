#include "systemControl.hpp"

#include "devices/devices.hpp"
#include "devices/trayController.hpp"

void driveToggle() {
  if (driveToggleButton.changedToPressed()) isArcadeDrive = !isArcadeDrive;

  if (isArcadeDrive)
    model->arcade(controller.getAnalog(okapi::ControllerAnalog::leftY),
                  -controller.getAnalog(okapi::ControllerAnalog::rightX));
  else
    model->tank(controller.getAnalog(okapi::ControllerAnalog::rightY),
                controller.getAnalog(okapi::ControllerAnalog::leftY));
}

void trayControl() {
  if (trayButton.changedToPressed()) {
    if (trayIsMoving) {
      trayController.cancelled = true;
      trayIsMoving = false;
    } else if (trayIsUp && !trayIsMoving) {
      std::cout << "Lowering tray \n";
      trayIsMoving = true;
      trayController.state = TrayStates::down;
      trayIsUp = false;
    } else if (!trayIsUp && !trayIsMoving) {
      std::cout << "Raising tray \n";
      trayIsMoving = true;
      trayController.state = TrayStates::up;
      trayIsUp = true;
    }
  } else if (antitipDeployButton.changedToPressed()) {
    if (trayIsUp) {
      std::cout << "Lowering tray \n";
      trayIsMoving = true;
      trayController.state = TrayStates::down;
      trayIsUp = false;
    } else {
      std::cout << "Raising tray to deploy antitips \n";
      trayIsMoving = true;
      trayController.state = TrayStates::slightlyUp;
      trayIsUp = true;
    }
  }
}

void trayTaskFn() {
  while (1) {
    switch (trayController.state) {
      case TrayStates::up:
        trayController.raise();
        std::cout << "Tray Raised \n";
        trayController.state = TrayStates::holding;
        break;

      case TrayStates::down:
        trayController.lower();
        std::cout << "Tray Lowered \n";
        trayController.state = TrayStates::holding;
        break;

      case TrayStates::slightlyUp:
        trayController.raise(200);  // TODO: tune this value if needed
        trayController.state = TrayStates::holding;
        break;

      case TrayStates::holding:
        trayIsMoving = false;
        trayController.trayMotor->setBrakeMode(
            okapi::AbstractMotor::brakeMode::hold);
        trayController.trayMotor->moveVelocity(0);
        break;

      case TrayStates::off:
        trayController.trayMotor->setBrakeMode(
            okapi::AbstractMotor::brakeMode::coast);
        trayController.trayMotor->moveVoltage(0);
        break;

      default:
        std::cout << "Invalid TrayState passed \n";
        break;
    }

    pros::delay(20);
  }
}

void liftControl() {
  lift.setBrakeMode(AbstractMotor::brakeMode::hold);

  if (liftUpButton.isPressed()) {
    lift.moveVelocity(150);
  } else if (liftDownButton.isPressed()) {
    lift.moveVelocity(-70);
  } else if (pot.get() < 3400) {
    lift.moveVelocity(0);
  } else {
    lift.moveVoltage(0);
  }
}

void rollerBrakeManagement() {
  if (trayController.coastRollers())  // Fix this
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  else
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}

void rollerControl() {
  if (intakeButton.isPressed())
    rollers.moveVelocity(200);
  else if (outtakeButton.isPressed())
    rollers.moveVelocity(-150);
  else
    rollers.moveVelocity(0);
}