#include "devices.hpp"

okapi::ControllerButton intakeButton = okapi::ControllerDigital::R2;
okapi::ControllerButton trayButton = okapi::ControllerDigital::A;
okapi::ControllerButton outtakeButton = okapi::ControllerDigital::R1;
okapi::ControllerButton liftUpButton = okapi::ControllerDigital::L1;
okapi::ControllerButton liftDownButton = okapi::ControllerDigital::L2;
okapi::ControllerButton	driverDan = okapi::ControllerDigital::B;

okapi::MotorGroup rollers = MotorGroup({ -11, 15 });
TrayController tray(6);
okapi::Motor lift(13, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

okapi::ChassisScales scales
{
	{4.125_in, 10.1_in},
	imev5GreenTPR
};
okapi::Controller controller;

std::shared_ptr<okapi::ChassisController> chassis = okapi::ChassisControllerBuilder()
										.withMotors({ -1, -3 }, { 2, 4 })
										.withGearset(okapi::AbstractMotor::gearset::green)
										.withDimensions(scales)
										.build();

// TODO: tune max velocity
std::shared_ptr<okapi::OdomChassisController> autChassis = okapi::ChassisControllerBuilder()
										.withMotors({ -1, -3 }, { 2, 4 })
										.withGearset(okapi::AbstractMotor::gearset::green)
										.withDimensions(scales)
										.withMaxVelocity(75)
										.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_mm, 0_deg, 0.00001_mps)
										.buildOdometry();
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());

pros::ADILineSensor lineSensor = pros::ADILineSensor('H');

bool trayToggle = false;
bool danIsDriving = false;