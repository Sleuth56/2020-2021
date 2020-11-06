#include "main.h"

ADIEncoder leftEncoder('G', 'H');
ADIEncoder rightEncoder('E', 'F');

bool chassisBrake = false;

Motor frontLeftMotor(13, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor backLeftMotor(20, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor frontRightMotor(14, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor backRightMotor(18, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
	.withMotors(frontLeftMotor, frontRightMotor, backRightMotor, backLeftMotor)
  .withMaxVelocity(150)
  .withSensors(leftEncoder, rightEncoder)
    .withGains(
        {0.0025, 0, 0}, // Distance controller gains
        {0.002, 0, 0}, // Turn controller gains
        {0.002, 0, 0.00006}  // Angle controller gains (helps drive straight)
    )
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 12_in}, imev5GreenTPR})
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

std::shared_ptr<okapi::SkidSteerModel> driveTrain = std::dynamic_pointer_cast<SkidSteerModel>(chassis->getModel());

// Thread that controls the chassis 
void ChassisOpcontrol(void* param) {
  // chassis->moveDistance(0_in);
  // assigning the chassis to a X-drive model
  // driveTrain->setBrakeMode(AbstractMotor::brakeMode::hold);
  
  // int leftMotorControl = 0;
  // int rightMotorControl = 0;
  // int middleMotorControl = 0;

  while (isAuton == false) {
    //Updates display values.
		updateLineVariable(4, leftEncoder.get());
		updateLineVariable(5, rightEncoder.get());
    
    // // Graphs the drive motor temps
    lv_chart_set_next(chart, NavyLine, frontLeftMotor.getTemperature());
    lv_chart_set_next(chart, BlueLine, backLeftMotor.getTemperature());
    lv_chart_set_next(chart, GreenLine, frontRightMotor.getTemperature());
    lv_chart_set_next(chart, LimeLine, backRightMotor.getTemperature());

    chassis->getModel()->arcade(master.getAnalog(ControllerAnalog::leftY), master.getAnalog(ControllerAnalog::rightX), 0.3);
    pros::delay(20);
  }
}