#include "devices/devices.hpp"
#include "systemControl.hpp"
#include "devices/trayController.hpp"

void driveToggle() {
  if(driverDan.changedToPressed())
    danIsDriving = !danIsDriving;

  if(danIsDriving == true)
    model->arcade(controller.getAnalog(okapi::ControllerAnalog::leftY),
      -controller.getAnalog(okapi::ControllerAnalog::rightX));
  else
    model->tank(controller.getAnalog(okapi::ControllerAnalog::rightY),
          controller.getAnalog(okapi::ControllerAnalog::leftY));
}

void trayControl() {
  if(trayKillButton.isPressed()) {
    trayController.state = TrayStates::off;
    
    trayIsUp = false;
  } else if(trayButton.changedToPressed()) {
    if(trayIsUp) {
      trayController.state = TrayStates::down;
    } else {
      trayController.state = TrayStates::up;
    }

    trayIsUp = !trayIsUp;
  }
}

void trayTaskFn() {
  while(1) {
    switch(trayController.state) {
      case TrayStates::up:
      trayController.raise();
      trayController.state = TrayStates::holding;
      break;

      case TrayStates::down:
      trayController.lower();
      trayController.state = TrayStates::holding;
      break;

      case TrayStates::slightlyUp:
      trayController.raise(200);  // TODO: tune this value if needed
      trayController.state = TrayStates::holding;
      break;

      case TrayStates::holding:
      trayController.trayMotor->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
      trayController.trayMotor->moveVelocity(0);
      break;

      case TrayStates::off:
      trayController.trayMotor->setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
      trayController.trayMotor->moveVoltage(0);
      break;

      default:
      std::cout << "Invalid TrayState passed \n";
      break; 
    }
  }
}

void liftControl() {
  if(liftUpButton.isPressed()) {
    lift.moveVelocity(100);
  }
  else if(liftDownButton.isPressed()) {
    lift.moveVelocity(-70);
  }
  else {
    lift.moveVelocity(0);
  }
}

void rollerBrakeManagement() {
  if(trayController.coastRollers()) // Fix this
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  else
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
}

void rollerControl() {
  if(intakeButton.isPressed())
    rollers.moveVelocity(200);
  else if(outtakeButton.isPressed())
    rollers.moveVelocity(-120);
  else
    rollers.moveVelocity(0);
}