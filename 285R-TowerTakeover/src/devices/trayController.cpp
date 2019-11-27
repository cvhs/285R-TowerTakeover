#include "trayController.hpp"

TrayController::TrayController(int iangler) :
angler(new okapi::Motor(iangler)), task(taskFnc, this, "Tray Controller") {
  angler->setGearing(okapi::AbstractMotor::gearset::red);
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
        case off:
        angler->moveVoltage(0);
        break;

        case holding:
        angler->moveVelocity(0);
        break;

        case up:
        angler->moveAbsolute(2400, 90);
        pros::delay(800);
        angler->moveAbsolute(3100, 50);
        pros::delay(1300);
        trayState = trayStates::off;
        trayToggle = true;
        break;

        case down:
        angler->moveAbsolute(0, 80);
        pros::delay(2000);
        trayState = trayStates::off;
        trayToggle = false;
        break;

        case armup:
        std::cout << "trayState: armup" << std::endl;
        pros::delay(300);
        angler->moveAbsolute(1350, 85);
        trayToggle = true;
        break;

        case armdown:
        angler->moveAbsolute(0, 100);
        pros::delay(1000);
        trayState = trayStates::off;
        trayToggle = false;
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
