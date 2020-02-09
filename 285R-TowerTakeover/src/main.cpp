#include "devices/devices.hpp"
#include "comp/comp.hpp"

void initialize() {
	lineSensor.calibrate();
	// imu.reset();
	generatePaths();
	// pros::delay(2000);
	
	pros::Task trayTask(trayTaskFn);
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	deploy();
	// pros::delay(1000);
	// twoCube();
	oneCube();
	trayController.state = TrayStates::slightlyUp;
	trayIsUp = true;
	pros::delay(1000);
	trayController.state = TrayStates::down;
	// autChassis->moveDistance(1_ft);
	// rollers.moveVelocity(-60);
	// autChassis->moveDistance(-1_ft);
	// redSmall5Cube();



	// while(lineSensor.get_value() == 0){}
	// int val = pot.get();
	// int aut = val <= 1023 ? 0 : val <= 2047 ? 1 : val <= 3071 ? 2 : 3;

	// rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

	// switch(aut) {
	// 	case 0: // red
	// 	// red5CubesCartesian();
	// 	break;

	// 	case 1: // blue
	// 	// blue5CubesCartesian();
	// 	break;

	// 	case 2: // one cube
	// 	// oneCube();
	// 	break;

	// 	case 3: // no aut
	// 	break;

	// 	default:
	// 	break;
	// }
}

void opcontrol()
{
	while(1)
	{
		lift.setBrakeMode(AbstractMotor::brakeMode::hold);

		// chassisWidthTest(5);
		
		driveToggle();

		trayControl();
		liftControl();
		rollerControl();

		rollerBrakeManagement();

		pros::delay(20);
	}

}
