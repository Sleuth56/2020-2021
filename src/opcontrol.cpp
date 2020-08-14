#include "main.h"

// controller declaration
Controller master (ControllerId::master);
Controller partner (ControllerId::partner);

Motor RightRollerMotor(11, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor LeftRollerMotor(21, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor Intake(20, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor OutTake(12, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
MotorGroup Roller({11, -21});

int startingAnglerAngle;

void opcontrol() {
  isAuton = false;
  lv_tabview_set_tab_act(tabview, 3, true);
  chassis->setTurnsMirrored(false);
  // Seting the motor brake mode to hold
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
  Roller.setBrakeMode(AbstractMotor::brakeMode::hold);
  OutTake.setBrakeMode(AbstractMotor::brakeMode::hold);
  
  // Creating controller buttons
  // ControllerButton leftScreenButton(ControllerDigital::up);

  // Start the thread for the base
  pros::Task ChassisOpcontrol_TR(ChassisOpcontrol, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Chassis Task");
  while (true) {
    lv_chart_set_next(chart, SilverLine, LeftRollerMotor.getTemperature());
    lv_chart_set_next(chart, WhiteLine, RightRollerMotor.getTemperature());
    lv_chart_set_next(chart, PurpleLine, Intake.getTemperature());
    lv_chart_set_next(chart, OrangeLine, OutTake.getTemperature());

    if (master.getDigital(ControllerDigital::L2)) {
      Intake.moveVelocity(500);
      Roller.moveVelocity(200);
    }
    else if (master.getDigital(ControllerDigital::L1)) {
      Intake.moveVelocity(-500);
      Roller.moveVelocity(-200);
    }
    else {
      Intake.moveVelocity(0);
      Roller.moveVelocity(0);
    }

    if (master.getDigital(ControllerDigital::R2)) {
      OutTake.moveVelocity(600);
      Intake.moveVelocity(500);
    }
    else if (master.getDigital(ControllerDigital::R1)) {
      OutTake.moveVelocity(-600);
      Intake.moveVelocity(-500);
    }
    else {
      OutTake.moveVelocity(0);
    }

    pros::delay(20);
  }
}
