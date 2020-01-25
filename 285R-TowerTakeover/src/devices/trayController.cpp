#include "trayController.hpp"

bool trayToggle = false;

TrayController::TrayController(std::shared_ptr<okapi::Motor> imotor) :
    trayMotor(imotor) {}

