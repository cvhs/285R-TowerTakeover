#include "devices.hpp"

bool onFire {false};

okapi::ControllerButton intakeButton = okapi::ControllerDigital::R2;
okapi::ControllerButton trayButton = okapi::ControllerDigital::L1;
okapi::ControllerButton outtakeButton = okapi::ControllerDigital::R1;
okapi::ControllerButton liftUpButton = okapi::ControllerDigital::up;
okapi::ControllerButton liftDownButton = okapi::ControllerDigital::down;
okapi::ControllerButton	driverDan = okapi::ControllerDigital::B;

okapi::MotorGroup rollers = MotorGroup({ -12, 14 });
TrayController tray(6, 1500);
okapi::Motor lift(13, true, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);
// ArmController arm(13);

okapi::ChassisScales scales
{
	{4.125_in, 9.75_in},
	imev5GreenTPR
};
okapi::Controller controller;

bool trayToggle = false;
bool danIsDriving = false;

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous()
{
	std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
										.withMotors({ -1, -3 }, { 2, 4 })
										.withGearset(okapi::AbstractMotor::gearset::green)
										.withDimensions(scales)
										.withMaxVelocity(60)
										.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_mm, 0_deg, 0.00001_mps)
										.buildOdometry();
	std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());
	// auto profile = okapi::AsyncMotionProfileControllerBuilder().withOutput(model, scales, okapi::AbstractMotor::GearsetRatioPair(okapi::AbstractMotor::gearset::green));


	// tray.setState(TrayController::trayStates::armup);
	// lift.moveAbsolute(640, 80);
	// pros::delay(2000);
	// tray.setState(TrayController::trayStates::armdown);
	// lift.moveAbsolute(0, 60);
	// pros::delay(1000);

	chassis->moveDistance(1_ft);
	pros::delay(1000);
	chassis->moveDistance(-1_ft);


	// if(onFire)
	// {
	// 	rollers.moveVelocity(80);
	// 	chassis->setState({0.5_ft, 9.75_ft, 0_deg});
	// 	chassis->driveToPoint({4.5_ft, 9.75_ft});
	// 	pros::delay(250);
	// 	rollers.moveVelocity(0);
	// 	// chassis->driveToPoint({1.8_ft, 9.75_ft}, true);
	// 	// chassis->waitUntilSettled();
	// 	// chassis->turnToAngle(235_deg);
	// 	// tray.setState(TrayController::trayStates::up);
	// }
	// else
	// {
	// 	rollers.moveVelocity(80);
	// 	chassis->setState({11.5_ft, 9.75_ft, 180_deg});
	// 	chassis->driveToPoint({7.5_ft, 9.75_ft});
	// 	pros::delay(300);
	// 	rollers.moveVelocity(0);
	// 	chassis->driveToPoint({11_ft, 7.2_ft}, false, 40_cm);
	// 	chassis->waitUntilSettled();
	// 	tray.setState(TrayController::trayStates::up);
	// 	pros::delay(500);
	// 	chassis->moveDistance(-1_ft);
	// }
}

void opcontrol()
{
	std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
										.withMotors({ -1, -3 }, { 2, 4 })
										.withGearset(okapi::AbstractMotor::gearset::green)
										.withDimensions(scales)
										.withOdometry(okapi::StateMode::FRAME_TRANSFORMATION, 0_mm, 0_deg, 0.0001_mps)
										.buildOdometry();
	std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());



	// arm.arm->tarePosition();

	while(1)
	{
		lift.setBrakeMode(AbstractMotor::brakeMode::hold);
		if(driverDan.changedToPressed())
			danIsDriving = !danIsDriving;
		if(danIsDriving == true)
			model->arcade(controller.getAnalog(okapi::ControllerAnalog::leftY),
				-controller.getAnalog(okapi::ControllerAnalog::rightX));
		else
			model->tank(controller.getAnalog(okapi::ControllerAnalog::rightY),
						controller.getAnalog(okapi::ControllerAnalog::leftY));


		if(trayButton.changedToPressed())
		{
			if(trayToggle)
				tray.setState(TrayController::trayStates::down);
			else
				tray.setState(TrayController::trayStates::up);
		}
		else if(liftUpButton.isPressed())
		{
			tray.setState(TrayController::trayStates::armup);
			lift.moveVelocity(100);
			// pros::delay(800);
			// tray.setState(TrayController::trayStates::armdown);
			// lift.moveAbsolute(0, 60);
			// if(armToggle)
			// {
			// 	tray.setState(TrayController::trayStates::armdown);
			// 	arm.setState(ArmController::armStates::down);
			// }
			// else
			// {
			// 	tray.setState(TrayController::trayStates::armup);
			// 	arm.setState(ArmController::armStates::up);
			// }
		}
		else if(liftDownButton.isPressed())
		{
			lift.moveVelocity(-60);
			if(lift.getPosition() <= 250){
				tray.setState(TrayController::trayStates::armdown);
			}
		}
		else {
			lift.moveVelocity(0);
		}

		// if(arm.getState() == ArmController::armStates::off)
		// 	arm.arm->setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
		// else
		// 	arm.arm->setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

		if(tray.getState() == TrayController::trayStates::off || tray.getState() == TrayController::trayStates::armup || tray.getState() == TrayController::trayStates::armdown)
			rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
		else
			rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

		if(intakeButton.isPressed())
			rollers.moveVelocity(160);
		else if(outtakeButton.isPressed())
			rollers.moveVelocity(-120);
		else
			rollers.moveVelocity(0);

		// if(controller.getDigital(okapi::ControllerDigital::left))
		// 	arm.setState(ArmController::armStates::kill);
	}

}
