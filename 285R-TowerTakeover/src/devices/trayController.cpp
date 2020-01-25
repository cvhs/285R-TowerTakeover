#include "trayController.hpp"

bool trayToggle = false;

TrayController::TrayController(std::shared_ptr<okapi::Motor> imotor) :
    trayMotor(imotor) {}

void TrayController::raise() {
    settled = false;
    while(!settled) {
        double error = stackLevel - trayMotor->getPosition();
        std::cout << error << "\n";
        trayMotor->moveVelocity(0.22 * (error));
        if(std::abs(error) < 8) settled = true;
    }
}

void TrayController::lower() {
    settled = true;
    while(!settled) {
        double error = 0 - trayMotor->getPosition();
        std::cout << error << "\n";
        trayMotor->moveVelocity(0.4 * (error));
        if(std::abs(error) < 8) settled = true;
    }
}

bool TrayController::coastRollers() {
    return trayMotor->getPosition() > 200;
}
