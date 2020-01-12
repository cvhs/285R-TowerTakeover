#include "devices/devices.hpp"
#include "systemControl.hpp"

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
  if(trayButton.changedToPressed()) {
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    if(trayToggle)
      tray.setState(TrayController::trayStates::down);
    else
      tray.setState(TrayController::trayStates::up);
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
  if(tray.coastRollers())
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