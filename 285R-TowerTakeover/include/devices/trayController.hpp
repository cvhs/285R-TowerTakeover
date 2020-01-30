#pragma once
#include "main.h"

extern bool trayToggle;

class TrayController {
    public:
    const double stackLevel = 900;
    const double coastLevel = 200;
    const double kPUp = 0.22;
    const double kPDown = 0.4;
    const settleLimit = 8;
    
    double error;
    bool settled;
    std::shared_ptr<okapi::Motor> trayMotor;

    TrayController(std::shared_ptr<okapi::Motor> imotor);
    void raise();
    void lower();
    bool coastRollers();
};