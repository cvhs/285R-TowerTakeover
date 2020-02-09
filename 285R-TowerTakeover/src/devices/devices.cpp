#include "devices.hpp"

okapi::ControllerButton intakeButton = okapi::ControllerDigital::R2;
okapi::ControllerButton trayButton = okapi::ControllerDigital::A;
okapi::ControllerButton trayKillButton = okapi::ControllerDigital::X;
okapi::ControllerButton outtakeButton = okapi::ControllerDigital::R1;
okapi::ControllerButton liftUpButton = okapi::ControllerDigital::L1;
okapi::ControllerButton liftDownButton = okapi::ControllerDigital::L2;
okapi::ControllerButton	driverDan = okapi::ControllerDigital::B;

const int rightRollerPort = -5;
const int leftRollerPort = 8;
const int liftPort = 4;
const int trayPort = 11;
const int blDrivePort = -9; //15
const int flDrivePort = -17; //13
const int brDrivePort = 18; //9
const int frDrivePort = 13; //17
const int imuPort = 19;

const okapi::ChassisScales scales
{
	{4.125_in, 10.2_in},
	imev5GreenTPR
};

okapi::MotorGroup rollers({rightRollerPort, leftRollerPort});

okapi::Motor lift(
	liftPort, false, 
	okapi::AbstractMotor::gearset::red, 
	okapi::AbstractMotor::encoderUnits::degrees
);

std::shared_ptr<okapi::Motor> tray = std::make_shared<okapi::Motor>(
	trayPort, false, 
	okapi::AbstractMotor::gearset::red, 
	okapi::AbstractMotor::encoderUnits::degrees
);

TrayController trayController = TrayController(tray);

okapi::Controller controller;

std::shared_ptr<okapi::ChassisController> chassis = okapi::ChassisControllerBuilder()
										.withMotors({blDrivePort, flDrivePort}, {brDrivePort, frDrivePort})
										.withDimensions(okapi::AbstractMotor::gearset::green, scales)
										.build();

// TODO: tune max velocity
std::shared_ptr<okapi::OdomChassisController> autChassis = okapi::ChassisControllerBuilder()
										.withMotors({blDrivePort, flDrivePort}, {brDrivePort, frDrivePort})
										.withDimensions(okapi::AbstractMotor::gearset::green, scales)
										.withMaxVelocity(90)
										.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_mm, 0_deg)
										.buildOdometry();

std::shared_ptr<okapi::ChassisModel> model = std::static_pointer_cast<okapi::ChassisModel>(autChassis->getModel());

std::shared_ptr<okapi::AsyncMotionProfileController> profiler = okapi::AsyncMotionProfileControllerBuilder()
										.withOutput(autChassis)
										.withLimits({1.0, 2.0, 10.0}) // TODO: tune these
										.buildMotionProfileController();

pros::ADILineSensor lineSensor = pros::ADILineSensor('A');
okapi::Potentiometer pot = okapi::Potentiometer('H');
pros::Imu imu = pros::Imu(imuPort);

bool danIsDriving = false;