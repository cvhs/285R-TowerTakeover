#include "trayController.hpp"

TrayController::TrayController(int iangler) :
angler(new okapi::Motor(iangler)), task(taskFnc, this, "Tray Controller") {
  angler->setGearing(okapi::AbstractMotor::gearset::red);
  rollerCoastStates = {holding, up, movingUpFast, movingUpSlow};
}

void TrayController::setState(trayStates state) {trayState = state;}

TrayController::trayStates TrayController::getState() {return trayState;}

void TrayController::run() { 
  while(true)
  {
    angler->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    if(!disabled)
    {
      switch(trayState)
      {
        case up:
        trayState = trayStates::movingUpFast;
        break;

        case down:
        angler->moveAbsolute(0, 80);
        pros::delay(2000);
        trayState = trayStates::off;
        trayToggle = false;
        break;

        case movingUpFast:
        angler->moveVelocity(90);
        if(angler.getPosition() >= 2400) trayState = trayStates::movingUpSlow;
        break;

        case movingUpSlow:
        angler->moveAbsolute(3100, 50);
        if(angler.isStopped()) trayState = trayStates::holding;
        break;

        case holding:
        angler->moveVelocity(0);
        break;

        case off:
        angler->moveVoltage(0);
        break;
      }
    }
    pros::delay(10);
  }
}


void TrayController::taskFnc(void* input)
{
  pros::delay(500);
  TrayController* that = static_cast<TrayController*>(input);
  that->run();
}
