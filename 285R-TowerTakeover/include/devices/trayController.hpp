#pragma once
#include "main.h"

extern bool trayToggle;

class TrayController {
    public:
    double stackLevel = 900;
    double error;
    bool settled;
    std::shared_ptr<okapi::Motor> trayMotor;

    TrayController(std::shared_ptr<okapi::Motor> imotor);
    void raise();
    void lower();
    bool coastRollers();
};