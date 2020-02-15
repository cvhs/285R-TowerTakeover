#include "trayController.hpp"

bool trayIsUp = false;

TrayController::TrayController(std::shared_ptr<okapi::Motor> imotor)
    : trayMotor(imotor) {
  state = TrayStates::off;
}

void TrayController::raise(double level) {
  settled = false;

  while (!settled) {
    double current = trayMotor->getPosition();
    double error = level - current;
    // std::cout << error << "\n";
    trayMotor->moveVelocity(kPUp * (error));

    settled = (current > level - 100) && (trayMotor->getActualVelocity() < 5);
  }
}

void TrayController::lower(double level) {
  settled = false;

  while (!settled) {
    double error = level - trayMotor->getPosition();
    // std::cout << error << "\n";
    trayMotor->moveVelocity(kPDown * (error));

<<<<<<< HEAD
        if(std::abs(error) < settleLimit) settled = true;
    }

    settled = true;
=======
    if (std::abs(error) < settleLimit) settled = true;
  }
>>>>>>> 9d4b3e4104f426fa876dfdcb89ba36149f998614
}

bool TrayController::coastRollers() {
  return trayMotor->getPosition() > coastLevel;
}