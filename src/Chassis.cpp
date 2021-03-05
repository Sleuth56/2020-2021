#include "main.h"

RotationSensor leftEncoder(9, true);
RotationSensor rightEncoder(10, true);

bool chassisBrake = false;

Motor frontLeftMotor(7, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor backLeftMotor(8, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor frontRightMotor(4, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor backRightMotor(6, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

std::shared_ptr<OdomChassisController> chassis =ChassisControllerBuilder()
    .withMaxVelocity(100)
    .withMotors({7, 8}, {-6, -4})
    .withGains(
        {0.0022, 0.000003, 0.000003}, // distance controller gains
        {0.0057, 0, 0.000004}, // turn controller gains
        {0.002, 0, 0.000004}  // angle controller gains (helps drive straight)
    )
    // green gearset, 4 inch wheel diameter, 11.5 inch wheelbase
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 12_in}, imev5GreenTPR})
    .withSensors(leftEncoder, rightEncoder)
    // specify the tracking wheels diameter (2.75 in), track (7 in), and TPR (360)
    .withOdometry({{4_in, 12_in}, quadEncoderTPR}, StateMode::FRAME_TRANSFORMATION)
    .buildOdometry();

// std::shared_ptr<okapi::SkidSteerModel> driveTrain = std::dynamic_pointer_cast<SkidSteerModel>(chassis->getModel());

// Thread that controls the chassis
void ChassisOpcontrol(void* param) {
  chassis.get()->stop();
  double CubedTurn = 0;
  double MasterY = 0;

  while (isAuton == false) {
    //Updates display values.
		updateLineVariable(4, leftEncoder.get());
		updateLineVariable(5, rightEncoder.get());
    
    // Graphs the drive motor temps
    lv_chart_set_next(chart, NavyLine, frontLeftMotor.getTemperature());
    lv_chart_set_next(chart, BlueLine, backLeftMotor.getTemperature());
    lv_chart_set_next(chart, GreenLine, frontRightMotor.getTemperature());
    lv_chart_set_next(chart, LimeLine, backRightMotor.getTemperature());

    if (abs(master.getAnalog(ControllerAnalog::rightX)) > 0) {
      CubedTurn = ((master.getAnalog(ControllerAnalog::rightX) * master.getAnalog(ControllerAnalog::rightX) * master.getAnalog(ControllerAnalog::rightX) / 1.5));}
    else {CubedTurn = 0;}

    if (abs(master.getAnalog(ControllerAnalog::leftY)) > 0) {MasterY = master.getAnalog(ControllerAnalog::leftY);}
    else {MasterY = 0;}

    chassis->getModel()->arcade(MasterY, CubedTurn, 0.1);
    pros::delay(20);
  }
}