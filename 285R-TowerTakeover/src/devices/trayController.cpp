#include "trayController.hpp"

TrayController::TrayController(int iangler, double ifinnese) :
angler(new okapi::Motor(iangler)), finnese(ifinnese), task(taskFnc, this, "Tray Controller") {
}

void TrayController::setState(trayStates state) {trayState = state;}

TrayController::trayStates TrayController::getState() {return trayState;}

void TrayController::disable()
{
  disabled = true;
}

void TrayController::enable() {disabled = false;}

void TrayController::run()
{
  angler->setGearing(okapi::AbstractMotor::gearset::red);
  while(true)
  {
    angler->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

    if(!disabled)
    {
      switch(trayState)
      {
        case off:
        angler->moveVelocity(0);
        break;

        case up:
        std::cout << "trayState: up" << std::endl;
        angler->moveAbsolute(2900, 60);
        pros::delay(1500);
        angler->moveAbsolute(3100, 50);
        pros::delay(1500);
        trayState = trayStates::off;
        std::cout << "trayState: off" << std::endl;
        trayToggle = true;
        break;

        case down:
        std::cout << "trayState: down" << std::endl;
        angler->moveAbsolute(0, 80);
        pros::delay(2000);
        trayState = trayStates::off;
        std::cout << "trayState: off" << std::endl;
        trayToggle = false;
        break;

        case armup:
        std::cout << "trayState: armup" << std::endl;
        pros::delay(300);
        angler->moveAbsolute(1350, 60);
        pros::delay(2000);
        trayState = trayStates::off;
        std::cout << "trayState: off" << std::endl;
        trayToggle = true;
        break;

        case armdown:
        std::cout << "trayState: armdown" << std::endl;
        angler->moveAbsolute(0, 60);
        pros::delay(1000);
        trayState = trayStates::off;
        std::cout << "trayState: off" << std::endl;
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
