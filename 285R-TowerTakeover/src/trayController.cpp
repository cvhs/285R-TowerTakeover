#include "trayController.hpp"

TrayController::TrayController(Motor* iangler, double ifinnese) : angler(iangler), finnese(ifinnese), task(taskFnc, this) {}

void TrayController::setState(trayStates state) {trayState = state;}

TrayController::trayStates TrayController::getState() {return trayState;}

void TrayController::disable()
{
  if(!disabled)
    angler->moveVelocity(0);

  disabled = true;
}

void TrayController::enable() {disabled = false;}


void TrayController::run()
{
  angler->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

  while(true)
  {
    if(!disabled)
    {
      switch(trayState)
      {
        case off:
        angler->moveVoltage(0);
        break;

        case up:
        angler->moveVelocity(10000);
        pros::delay(finnese);
        break;

        case down:
        angler->moveVelocity(-10000);
        pros::delay(50);
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
