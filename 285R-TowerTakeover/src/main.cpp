#include "devices/devices.hpp"
#include "comp/comp.hpp"

void initialize() {
	okapi::Logger::setDefaultLogger(
		std::make_shared<okapi::Logger>(
			okapi::TimeUtilFactory::createDefault().getTimer(),
			"/ser/sout",
			okapi::Logger::LogLevel::debug
		)
	);
	lineSensor.calibrate();
	generatePaths();
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	while(lineSensor.get_value() == 0){}
	int val = pot.get();
	int aut = val <= 1023 ? 0 : val <= 2047 ? 1 : val <= 3071 ? 2 : 3;

	rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

	switch(aut) {
		case 0: // red
		// red5CubesCartesian();
		break;

		case 1: // blue
		// blue5CubesCartesian();
		break;

		case 2: // one cube
		// oneCube();
		break;

		case 3: // no aut
		break;

		default:
		break;
	}
}

void opcontrol()
{
	pros::Task trayTask(trayTaskFn);
	while(1)
	{
		lift.setBrakeMode(AbstractMotor::brakeMode::hold);

		// chassisWidthTest(5);
		
		driveToggle();

		// trayControl();
		liftControl();
		rollerControl();

		rollerBrakeManagement();

		pros::delay(20);
	}

}
