#include "main.h"

// controller declaration
Controller master (ControllerId::master);
Controller partner (ControllerId::partner);

DistanceSensor TopBallDetector(13);
DistanceSensor BottomBallDetector(11);

Motor RightRollerMotor(1, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor LeftRollerMotor(5, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor Intake(20, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor OutTake(19, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
MotorGroup Roller({5, -1});

int startingAnglerAngle;


void Diagnostics(void* param) {
	while (true) {
		updateLineVariable(2, TopBallDetector.get());
    updateLineVariable(3, BottomBallDetector.get());
    pros::delay(50);
	}
}

void opcontrol() {
  isAuton = false;
  lv_tabview_set_tab_act(tabview, 3, true);
  chassis->setTurnsMirrored(false);
  // Seting the motor brake mode to hold
  Intake.setBrakeMode(AbstractMotor::brakeMode::hold);
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
      Roller.moveVelocity(200);
      
      if (BottomBallDetector.get() > 60 || BottomBallDetector.get() == -1) {
        Intake.moveVelocity(600);
        OutTake.moveVelocity(600);
      }
      else {
        Intake.moveVelocity(0);
        OutTake.moveVelocity(0);
      }
    }
    else if (master.getDigital(ControllerDigital::L2)) {
      Intake.moveVelocity(-600);
      Roller.moveVelocity(-200);
      OutTake.moveVelocity(-600);
    }

    if (master.getDigital(ControllerDigital::R2)) {
      OutTake.moveVelocity(-600);
      Intake.moveVelocity(600);
    }
    else if (master.getDigital(ControllerDigital::R1)) {
      OutTake.moveVelocity(600);
      Intake.moveVelocity(600);
    }

    if (!master.getDigital(ControllerDigital::L1) && !master.getDigital(ControllerDigital::L2) && !master.getDigital(ControllerDigital::R1) && !master.getDigital(ControllerDigital::R2)) {
      OutTake.moveVelocity(0);
      Intake.moveVelocity(0);
      Roller.moveVelocity(0);
    }

    pros::delay(20);
  }
}
