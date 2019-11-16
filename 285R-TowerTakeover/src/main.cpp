#include "devices.hpp"

bool onFire {true};

okapi::ControllerButton intakeButton = okapi::ControllerDigital::R2;
okapi::ControllerButton trayButton = okapi::ControllerDigital::A;
okapi::ControllerButton outtakeButton = okapi::ControllerDigital::R1;
okapi::ControllerButton liftUpButton = okapi::ControllerDigital::L1;
okapi::ControllerButton liftDownButton = okapi::ControllerDigital::L2;
okapi::ControllerButton	driverDan = okapi::ControllerDigital::B;

okapi::MotorGroup rollers = MotorGroup({ -11, 15 });
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


	if(onFire)
	{
		rollers.moveVelocity(160);
		chassis->setState({0.5_ft, 9.75_ft, 0_deg});
		chassis->driveToPoint({4.5_ft, 9.75_ft});
		pros::delay(250);
		rollers.moveVelocity(0);
		chassis->driveToPoint({3.75_ft, 9.75_ft}, true);
		chassis->driveToPoint({1.5_ft, 9.0_ft});
		
		rollers.moveRelative(-850, 100);
		tray.setState(TrayController::trayStates::up);
		while(tray.getState() == TrayController::trayStates::up){}
		tray.setState(TrayController::trayStates::down);
		rollers.moveVelocity(-100);
		pros::delay(200);
		chassis->moveDistance(-1_ft);
		rollers.moveVelocity(0);
	}
	else
	{
		rollers.moveVelocity(160);
		chassis->setState({11.5_ft, 9.75_ft, 180_deg});
		chassis->driveToPoint({7.5_ft, 9.75_ft});
		pros::delay(250);
		rollers.moveVelocity(0);
		chassis->driveToPoint({8.25_ft, 9.75_ft}, true);
		chassis->driveToPoint({10_ft, 8.15_ft}, false, 0_in);

		rollers.moveRelative(-850, 100);
		tray.setState(TrayController::trayStates::up);
		while(tray.getState() == TrayController::trayStates::up){}
		tray.setState(TrayController::trayStates::down);
		rollers.moveVelocity(-100);
		pros::delay(200);
		chassis->moveDistance(-1_ft);
		rollers.moveVelocity(0);
	}
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
			rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
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
		else if(liftDownButton.isPressed() && lift.getPosition() >= 0)
		{
			lift.moveVelocity(-80);
			if(lift.getPosition() <= 280){
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
