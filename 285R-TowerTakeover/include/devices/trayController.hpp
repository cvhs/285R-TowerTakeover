#pragma once
#include "main.h"

extern bool trayToggle;

class TrayController {
    public:
    static constexpr double stackLevel = 900;
    const double coastLevel = 200;
    const double kPUp = 0.22;
    const double kPDown = 0.4;
    const double settleLimit = 8;

    double error;
    bool settled;
    std::shared_ptr<okapi::Motor> trayMotor;

    TrayController(std::shared_ptr<okapi::Motor> imotor);
    void raise(double level = stackLevel);
    void lower(double level = 0);
    bool coastRollers();
};