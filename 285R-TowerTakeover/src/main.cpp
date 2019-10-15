#include "devices.hpp"


ChassisScales scales{ {4.125_in, 10_in}, imev5GreenTPR };
// auto chassis = okapi::ChassisControllerBuilder()
// 																												  .withMotors({ -1, -3 }, { 2, 4 })
// 																												  // .withGearset(okapi::AbstractMotor::gearset::green)
// 																												  // .withDimensions(scales)
// 																													.build();
// 																												  // .withOdometry(okapi::StateMode::CARTESIAN, 0_mm, 0_deg, 0.0001_mps)
// 																												  // .buildOdometry();
// std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());
// std::shared_ptr<okapi::OdomChassisController> chassis = new okapi::OdomChassisController();

okapi::ControllerButton intakeButton = okapi::ControllerDigital::R2;
okapi::ControllerButton trayButton = okapi::ControllerDigital::L2;
okapi::ControllerButton upButton = okapi::ControllerDigital::R1;
okapi::ControllerButton downButton = okapi::ControllerDigital::L1;

okapi::MotorGroup rollers = MotorGroup({ -12, 14 });
okapi::Motor tilt = Motor(6);
okapi::Motor arm = Motor(-13);

okapi::Controller controller;

bool toggle = false;

trayStates trayState = off;

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol()
{
	auto chassis = okapi::ChassisControllerBuilder()
									  .withMotors({ -1, -3 }, { 2, 4 })
									  .withGearset(okapi::AbstractMotor::gearset::green)
									  .withDimensions(scales)
									  .withOdometry(okapi::StateMode::CARTESIAN, 0_mm, 0_deg, 0.0001_mps)
									  .buildOdometry();
auto model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());


	rollers.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	arm.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
	while(1)
	{
		model->tank(controller.getAnalog(okapi::ControllerAnalog::rightY),
								controller.getAnalog(okapi::ControllerAnalog::leftY));

		if(intakeButton.isPressed())
			rollers.moveVoltage(12000);
		else
			rollers.moveVoltage(0);

		if(upButton.isPressed())
			arm.moveVoltage(12000);
		else if(downButton.isPressed())
			arm.moveVoltage(-12000);
		else
			arm.moveVoltage(0);

		// if(controller.getDigital(okapi::ControllerDigital::X))
		if(trayButton.isPressed())
			toggle = !toggle;

		if(toggle)
			trayState = up;
		else
			trayState = off;

		switch(trayState)
		{
			case off:
			tilt.moveVoltage(0);
			break;

			case up:
			// tilt.moveVoltage(12000);
			tilt.moveAbsolute(1234, 100);
			break;

			case down:
			// tilt.moveVoltage(-12000);
			tilt.moveAbsolute(0, 100);
			break;
		}
	}

}
