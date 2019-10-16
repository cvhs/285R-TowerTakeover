#include "trayController.hpp"

TrayController::TrayController(Motor* iangler, double ifinnese) :
angler(iangler), finnese(ifinnese), task(taskFnc, this, "Tray Controller") {}

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
  angler->setGearing(okapi::AbstractMotor::gearset::red);
  while(true)
  {
    // angler->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    
    if(!disabled)
    {
      switch(trayState)
      {
        case off:
        angler->moveVoltage(0);
        break;

        case up:
        angler->moveRelative(2800, 60);
        pros::delay(2000);
        pros::delay(1000);
        angler->moveRelative(-2800, 50);
        pros::delay(1500);
        trayToggle = false;
        break;

        case down:
        // angler->moveVoltage(-10000);
        angler->moveVelocity(-80);
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
