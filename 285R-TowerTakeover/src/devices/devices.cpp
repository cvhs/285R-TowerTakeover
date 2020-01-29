#include "devices.hpp"

okapi::ControllerButton intakeButton = okapi::ControllerDigital::R2;
okapi::ControllerButton trayButton = okapi::ControllerDigital::A;
okapi::ControllerButton outtakeButton = okapi::ControllerDigital::R1;
okapi::ControllerButton liftUpButton = okapi::ControllerDigital::L1;
okapi::ControllerButton liftDownButton = okapi::ControllerDigital::L2;
okapi::ControllerButton	driverDan = okapi::ControllerDigital::B;

okapi::MotorGroup rollers = MotorGroup({ -5, 8 });

okapi::Motor lift(
	4, false, 
	okapi::AbstractMotor::gearset::red, 
	okapi::AbstractMotor::encoderUnits::degrees
);

std::shared_ptr<okapi::Motor> tray = std::make_shared<okapi::Motor>(
	11, false, 
	okapi::AbstractMotor::gearset::red, 
	okapi::AbstractMotor::encoderUnits::degrees
);

TrayController trayController = TrayController(tray);

okapi::ChassisScales scales
{
	{4.125_in, 10.2_in},
	imev5GreenTPR
};
okapi::Controller controller;

std::shared_ptr<okapi::ChassisController> chassis = okapi::ChassisControllerBuilder()
										.withMotors({ -10, -17 }, { 15, 13 })
										.withDimensions(okapi::AbstractMotor::gearset::green, scales)
										.build();

// TODO: tune max velocity
std::shared_ptr<okapi::OdomChassisController> autChassis = okapi::ChassisControllerBuilder()
										.withMotors({ -1, -3 }, { 2, 4 })
										.withDimensions(okapi::AbstractMotor::gearset::green, scales)
										.withMaxVelocity(75)
										.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_mm, 0_deg)
										.buildOdometry();
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());

std::shared_ptr<okapi::AsyncMotionProfileController> profiler = okapi::AsyncMotionProfileControllerBuilder()
										.withOutput(chassis)
										.withLimits({1.0, 2.0, 10.0}) // TODO: tune these
										.buildMotionProfileController();

pros::ADILineSensor lineSensor = pros::ADILineSensor('H');
okapi::Potentiometer pot = okapi::Potentiometer('B');

bool danIsDriving = false;