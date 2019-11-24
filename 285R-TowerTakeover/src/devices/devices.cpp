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
	{4.125_in, 10.2_in},
	imev5GreenTPR
};

std::shared_ptr<okapi::SkidSteerModel> model = std::make_shared<okapi::SkidSteerModel>(
	std::make_shared<okapi::MotorGroup>(MotorGroup({-1, -3})), 
	std::make_shared<okapi::MotorGroup>(MotorGroup({2, 4})),
	std::make_shared<okapi::IntegratedEncoder>(okapi::IntegratedEncoder(1, true)),
	std::make_shared<okapi::IntegratedEncoder>(okapi::IntegratedEncoder(2, false)),
	200.0, 12000.0
);

std::shared_ptr<okapi::TwoEncoderOdometry> odom = std::make_shared<okapi::TwoEncoderOdometry>(
	okapi::TimeUtilFactory::createDefault(),
	model, scales
);

std::shared_ptr<lib7842::OdomController> odomController = std::make_shared<lib7842::OdomController>(
	model, odom,
	std::make_unique<okapi::IterativePosPIDController>(
		okapi::IterativePosPIDController({0, 0, 0, 0}, okapi::TimeUtilFactory::createDefault())
	),
	std::make_unique<okapi::IterativePosPIDController>(
		okapi::IterativePosPIDController({0, 0, 0, 0}, okapi::TimeUtilFactory::createDefault())
	),
	std::make_unique<okapi::IterativePosPIDController>(
		okapi::IterativePosPIDController({0, 0, 0, 0}, okapi::TimeUtilFactory::createDefault())
	),
	1_mm
);

okapi::Controller controller;

pros::ADILineSensor lineSensor = pros::ADILineSensor('H');
okapi::Potentiometer pot = okapi::Potentiometer('B');

bool trayToggle = false;
bool danIsDriving = false;