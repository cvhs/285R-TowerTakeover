#include "trayController.hpp"

TrayController::TrayController(int iangler) :
angler(new okapi::Motor(iangler)), task(taskFnc, this, "Tray Controller") {
}

void TrayController::setState(trayStates state) {trayState = state;}

TrayController::trayStates TrayController::getState() {return trayState;}

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
        angler->moveAbsolute(2400, 90);
        pros::delay(800);
        angler->moveAbsolute(3100, 50);
        pros::delay(1300);
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
        angler->moveAbsolute(1350, 85);
        // pros::delay(1000);
        // trayState = trayStates::off;
        std::cout << "trayState: off" << std::endl;
        trayToggle = true;
        break;

        case armdown:
        std::cout << "trayState: armdown" << std::endl;
        angler->moveAbsolute(0, 100);
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
