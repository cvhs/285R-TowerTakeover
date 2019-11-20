#include "devices/devices.hpp"
#include "comp/autonFunctions.hpp"
#include "comp/opFunctions.hpp"

bool onFire {false};

void initialize() {
	lineSensor.calibrate();
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	while(lineSensor.get_value() == 0){}
	rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	if(onFire)
	{
		red5CubesCartesian();
	}
	else
	{
		blue5CubesCartesian();
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

	while(1)
	{
		lift.setBrakeMode(AbstractMotor::brakeMode::hold);

		// std::cout << lineSensor.get_value() << std::endl;

		// chassisWidthTest(5);
		
		driveToggle();

		trayAndLiftControl();

		rollerBrakeManagement();

		rollerControl();

		pros::delay(20);
	}

}
