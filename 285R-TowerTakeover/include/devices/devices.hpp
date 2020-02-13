#pragma once
#include "main.h"
#include "trayController.hpp"

extern std::shared_ptr<okapi::ChassisController> chassis;
extern std::shared_ptr<okapi::OdomChassisController> autChassis;
extern std::shared_ptr<okapi::ChassisModel> model;
extern std::shared_ptr<okapi::AsyncMotionProfileController> profiler;

extern okapi::MotorGroup rollers;
extern okapi::Motor lift;
extern std::shared_ptr<okapi::Motor> tray;
extern TrayController trayController;

extern okapi::ControllerButton trayButton;
extern okapi::ControllerButton trayKillButton;
extern okapi::ControllerButton intakeButton;
extern okapi::ControllerButton outtakeButton;
extern okapi::ControllerButton liftUpButton;
extern okapi::ControllerButton liftDownButton;
extern okapi::ControllerButton driverDan;

extern okapi::Controller controller;

extern pros::ADILineSensor lineSensor;
extern okapi::Potentiometer pot;
extern pros::Imu imu;
extern pros::ADIDigitalIn leftSwitch;
extern pros::ADIDigitalIn rightSwitch;

extern bool danIsDriving;