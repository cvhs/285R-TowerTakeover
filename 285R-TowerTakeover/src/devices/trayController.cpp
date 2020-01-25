#include "trayController.hpp"

bool trayToggle = false;

TrayController::TrayController(std::shared_ptr<okapi::Motor> imotor) :
    trayMotor(imotor) {}

void TrayController::raise() {
    settled = false;
    while(!settled) {
        double error = stackLevel - tray.getPosition();
        std::cout << error << "\n";
        tray.moveVelocity(0.22 * (error));
        if(std::abs(error) < 8) settled = true;
    }
}

void TrayController::lower() {
    settled = true;
    while(!settled) {
        double error = 0 - tray.getPosition();
        std::cout << error << "\n";
        tray.moveVelocity(0.4 * (error));
        if(std::abs(error) < 8) settled = true;
    }
}
