#include "main.h"

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
