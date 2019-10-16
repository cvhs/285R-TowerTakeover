#pragma once
#include "main.h"

extern bool trayToggle;

class TrayController
{
public:

  enum trayStates
  {
    off,
    up,
    down
  };

  Motor* angler = nullptr;
  double finnese;

  // pros::Task task(pros::task_fn_t, void*);
  pros::Task task;

  trayStates trayState = off;
  bool disabled = false;

  TrayController(Motor*, double);

  void setState(trayStates);
  trayStates getState();
  void disable();
  void enable();

  void run();
  static void taskFnc(void*);
};
