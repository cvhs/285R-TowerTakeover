#include "devices/devices.hpp"
#include "opcontrolUtils.hpp"

void chassisWidthTest(double numTurns){
  okapi::Motor left(-1);
  okapi::Motor right(2);

  double leftInch = left.getPosition()/360 * 4.125 * PI;
  double rightInch = right.getPosition()/360 * 4.125 * PI;

  double chassisWidth = (leftInch - rightInch) / (numTurns * 360);

  std::cout << "Calculated ChassisWidth: " << chassisWidth << std::endl;
}