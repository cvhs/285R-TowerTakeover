#include "devices.hpp"


void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

//* @param  iscales {straight scale, turn scale} or
//* {straight scale, turn scale, length to middle wheel in meters, middle scale}

ChassisScales scales{{4.125_in, 10_in}, imev5GreenTPR};
std::shared_ptr<okapi::ChassisController> chassis = okapi::ChassisControllerBuilder().withMotors({-1, -3}, {2, 4}).withGearset(okapi::AbstractMotor::gearset::green).withDimensions(scales).withOdometry(okapi::StateMode::CARTESIAN, 0_mm, 0_deg, 0.0001_mps).build();
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());

okapi::ControllerButton Intake = okapi::ControllerDigital::R2;
okapi::ControllerButton Tray = okapi::ControllerDigital::L2;
okapi::ControllerButton Up = okapi::ControllerDigital::R1;
okapi::ControllerButton Down = okapi::ControllerDigital::L1;

okapi::MotorGroup rollers({-12, 14});
okapi::Motor tilt(6);
okapi::Motor arm(13);

okapi::Controller controller;

bool toggle = false;

void opcontrol()
{
	model->tank(controller.getAnalog(okapi::ControllerAnalog::leftY),
							controller.getAnalog(okapi::ControllerAnalog::rightY));

	if(Intake.isPressed())
		rollers.moveVoltage(12000);
	else
		rollers.moveVoltage(0);

	
}
