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
  while(1) {
    if(trayButton.changedToPressed()) {
      rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
      std::cout << "Toggling tray" << "\n";
      if(trayToggle) {
        // trayController->setTarget(0);
        bool settled = false;
        while(!settled) {
          double error = 0 - tray.getPosition();
          std::cout << error << "\n";
          tray.moveVelocity(0.4 * (error));
          if(std::abs(error) < 8) settled = true;
        }
      }
      else {
        // trayController->setTarget(3100);
        bool settled = false;
        while(!settled) {
          double error = 900 - tray.getPosition();
          std::cout << error << "\n";
          tray.moveVelocity(0.22 * (error));
          if(std::abs(error) < 8) settled = true;
        }
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
  if(tray.getPosition() > 200) // Fix this
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