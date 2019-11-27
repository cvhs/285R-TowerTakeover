#include "../devices/devices.hpp"
#include "opFunctions.hpp"

void chassisWidthTest(double numTurns){
  okapi::Motor left(-1);
  okapi::Motor right(2);

  double leftInch = left.getPosition()/360 * 4.125 * PI;
  double rightInch = right.getPosition()/360 * 4.125 * PI;

  double chassisWidth = (leftInch - rightInch) / (numTurns * 360);

  std::cout << "Calculated ChassisWidth: " << chassisWidth << std::endl;
}

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

void trayAndLiftControl() {
  if(trayButton.changedToPressed()) {
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    if(trayToggle)
      tray.setState(TrayController::trayStates::down);
    else
      tray.setState(TrayController::trayStates::up);
  }
  else if(liftUpButton.isPressed()) {
    tray.setState(TrayController::trayStates::armup);
    lift.moveVelocity(100);
  }
  else if(liftDownButton.isPressed()) {
    lift.moveVelocity(-70);
    if(lift.getCurrentDraw() > 850){
      tray.setState(TrayController::trayStates::down);
    }
    std::cout << lift.getCurrentDraw() << std::endl;
  }
  else {
    lift.moveVelocity(0);
  }
}

void rollerBrakeManagement() {
  if(tray.getState() == TrayController::trayStates::off || tray.getState() == TrayController::trayStates::armup || tray.getState() == TrayController::trayStates::down)
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  else
    rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
}

void rollerControl() {
  if(intakeButton.isPressed())
    rollers.moveVelocity(200);
  else if(outtakeButton.isPressed())
    rollers.moveVelocity(-120);
  else
    rollers.moveVelocity(0);
}