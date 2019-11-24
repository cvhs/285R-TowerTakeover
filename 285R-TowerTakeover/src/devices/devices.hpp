#include "main.h"
#include "trayController.hpp"

extern okapi::ChassisScales scales;
extern std::shared_ptr<okapi::SkidSteerModel> model;
extern std::shared_ptr<okapi::TwoEncoderOdometry> odom;
extern std::shared_ptr<lib7842::OdomController> odomController;


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

extern pros::ADILineSensor lineSensor;
extern okapi::Potentiometer pot;

extern bool danIsDriving;