#pragma once
#include "main.h"
#include <set>

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
    down
  };

  std::array<trayStates, 4> rollerCoastStates;

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
