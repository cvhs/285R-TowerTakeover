#include "trayController.hpp"

bool trayIsUp = false;
bool trayIsMoving = false;

TrayController::TrayController(std::shared_ptr<okapi::Motor> imotor)
    : trayMotor(imotor) {
  state = TrayStates::off;
  cancelled = false;
}

void TrayController::raise(double level) {
  settled = false;

  while (!settled && !cancelled) {
    double current = trayMotor->getPosition();
    double error = level - current;
    // std::cout << error << "\n";
    trayMotor->moveVelocity(kPUp * (error));

    settled = (current > level - 100) && (trayMotor->getActualVelocity() < 5);
  }

  cancelled = false;
}

void TrayController::lower(double level) {
  settled = false;

  while (!settled && !cancelled) {
    double error = level - trayMotor->getPosition();
    // std::cout << error << "\n";
    trayMotor->moveVelocity(kPDown * (error));

    if (std::abs(error) < settleLimit) settled = true;
  }

  cancelled = false;
}

bool TrayController::coastRollers() {
  return trayMotor->getPosition() > coastLevel;
}