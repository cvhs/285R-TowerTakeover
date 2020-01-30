#include "trayController.hpp"

bool trayToggle = false;

TrayController::TrayController(std::shared_ptr<okapi::Motor> imotor) :
    trayMotor(imotor) {}

void TrayController::raise(double level = stackLevel) {
    settled = false;

    while(!settled) {
        double error = level - trayMotor->getPosition();
        std::cout << error << "\n";
        trayMotor->moveVelocity(kPUp * (error));

        if(std::abs(error) < settleLimit) settled = true;
    }
}

void TrayController::lower(double level = 0) {
    settled = true;

    while(!settled) {
        double error = level - trayMotor->getPosition();
        std::cout << error << "\n";
        trayMotor->moveVelocity(kPDown * (error));

        if(std::abs(error) < settleLimit) settled = true;
    }
}

bool TrayController::coastRollers() {
    return trayMotor->getPosition() > coastLevel;
}
