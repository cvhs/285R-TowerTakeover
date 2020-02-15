#include "devices/devices.hpp"
#include "comp/comp.hpp"


void initialize() {
	lineSensor.calibrate();
	// imu.reset();
	generatePaths();
	// while(imu.is_calibrating()) {
	// 	pros::delay(10);
	// }
	
	pros::Task trayTask(trayTaskFn);
	pros::Task autonSelectorTask(autonSelectorFn, "autonSelector");
}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	// imuTurn(90);
	tenCubes();
	// runAuton();
	// trayController.state = TrayStates::slightlyUp;
	// trayIsUp = true;
	// pros::delay(1000);
	// trayController.state = TrayStates::down;
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
