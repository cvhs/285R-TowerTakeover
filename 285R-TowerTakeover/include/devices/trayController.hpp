#pragma once
#include "main.h"

class TrayController {
    public:
    double stackLevel;
    double error;

    void raise();
    void lower();
};