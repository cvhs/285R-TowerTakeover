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
  while(1) {
    if(trayButton.changedToPressed()) {
      rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
      std::cout << "Toggling tray" << "\n";
      if(trayToggle) {
        trayController.lower();
      }
      else {
        trayController.raise();
      }
      trayToggle = !trayToggle;
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