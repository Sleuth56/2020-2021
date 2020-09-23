#include "main.h"

// controller declaration
Controller master (ControllerId::master);
Controller partner (ControllerId::partner);

pros::ADIAnalogIn TopBall('A');
pros::ADIAnalogIn BottomBall('B');

Motor RightRollerMotor(17, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor LeftRollerMotor(5, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor Intake(19, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor OutTake(15, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
MotorGroup Roller({-17, 5});

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

    if (master.getDigital(ControllerDigital::L1)) {
      Intake.moveVelocity(600);
      Roller.moveVelocity(400);
      if (TopBall.get_value() > 2800) {
        OutTake.moveVelocity(200);
      }
      else {
        OutTake.moveVelocity(0);
      }
    }
    else if (master.getDigital(ControllerDigital::L2)) {
      Intake.moveVelocity(-600);
      Roller.moveVelocity(-400);
      OutTake.moveVelocity(-600);
    }

    else if (master.getDigital(ControllerDigital::R2)) {
      OutTake.moveVelocity(-600);
      Intake.moveVelocity(600);
    }
    else if (master.getDigital(ControllerDigital::R1)) {
      OutTake.moveVelocity(600);
      Intake.moveVelocity(600);
    }

    else {
      OutTake.moveVelocity(0);
      Intake.moveVelocity(0);
      Roller.moveVelocity(0);
    }

    pros::delay(20);
  }
}
