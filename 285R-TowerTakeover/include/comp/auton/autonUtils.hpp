#pragma once

extern void stack();
extern void outtakeToStack();
extern void imuTurn(double degrees);
extern void deploy();

bool pathsLoaded();
extern void generatePaths();
extern void autonSelectorFn();
extern void runAuton();
extern int autonSelected;