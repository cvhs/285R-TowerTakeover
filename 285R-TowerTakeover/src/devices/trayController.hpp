#pragma once
#include "main.h"

extern bool trayToggle;

class TrayController
{
public:

  enum trayStates
  {
    off,
    holding,
    up,
    movingUpFast,
    movingUpSlow,
    down,
    armup,
    movingToArm
  };

  Motor* angler = nullptr;

  pros::Task task;

  trayStates trayState = off;
  bool disabled = false;

  TrayController(int);

  void setState(trayStates);
  trayStates getState();

  void run();
  static void taskFnc(void*);
};
