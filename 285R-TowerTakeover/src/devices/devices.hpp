#include "main.h"
#include "trayController.hpp"

extern okapi::ChassisScales scales;
extern std::shared_ptr<okapi::OdomChassisController> chassis;
extern std::shared_ptr<okapi::ChassisModel> model;

extern okapi::MotorGroup rollers;
extern okapi::Motor lift;
extern TrayController tray;

extern okapi::ControllerButton trayButton;
extern okapi::ControllerButton intakeButton;
extern okapi::ControllerButton outtakeButton;
extern okapi::ControllerButton liftUpButton;
extern okapi::ControllerButton liftDownButton;
extern okapi::ControllerButton driverDan;

extern okapi::Controller controller;

extern bool danIsDriving;