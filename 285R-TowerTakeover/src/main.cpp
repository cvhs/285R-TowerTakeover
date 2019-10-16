#include "devices.hpp"

okapi::ControllerButton intakeButton = okapi::ControllerDigital::R2;
okapi::ControllerButton trayButton = okapi::ControllerDigital::L2;
okapi::ControllerButton upButton = okapi::ControllerDigital::R1;
okapi::ControllerButton downButton = okapi::ControllerDigital::L1;

okapi::MotorGroup rollers = MotorGroup({ -12, 14 });
TrayController tray(new okapi::Motor(6), 75);
okapi::Motor arm = Motor(13,false, okapi::AbstractMotor::gearset::red, okapi::AbstractMotor::encoderUnits::degrees);

okapi::Controller controller;

bool toggle = false;

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
	}

}
