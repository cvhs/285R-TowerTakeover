#include "devices/devices.hpp"
#include "comp/autonFunctions.hpp"
#include "comp/opFunctions.hpp"

bool onFire {true};

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
	{4.125_in, 9.75_in},
	imev5GreenTPR
};
okapi::Controller controller;

std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
										.withMotors({ -1, -3 }, { 2, 4 })
										.withGearset(okapi::AbstractMotor::gearset::green)
										.withDimensions(scales)
										.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_mm, 0_deg, 0.00001_mps)
										.buildOdometry();
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());


bool trayToggle = false;
bool danIsDriving = false;

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	if(onFire)
	{
		red5Cubes();
	}
	else
	{
		blue5Cubes();
	}
}

void opcontrol()
{
	// std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
	// 									.withMotors({ -1, -3 }, { 2, 4 })
	// 									.withGearset(okapi::AbstractMotor::gearset::green)
	// 									.withDimensions(scales)
	// 									.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_mm, 0_deg, 0.0001_mps)
	// 									.buildOdometry();


	// arm.arm->tarePosition();

	while(1)
	{
		lift.setBrakeMode(AbstractMotor::brakeMode::hold);
		
		driveToggle();

		trayAndLiftControl();

		rollerBrakeManagement();

		rollerControl();

		pros::delay(20);
	}

}
