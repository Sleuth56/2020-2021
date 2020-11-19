#include "main.h"

// When set to true driver code stops
bool isAuton = false;

void blueSmall() {
  // set the state to zero
  chassis->setState({0_in, 0_in, 0_deg});
  Roller.moveVelocity(200); Intake.moveVelocity(500);
  chassis->driveToPoint({1.5_ft, 0_ft});
  // pros::delay(200);
  Roller.moveVelocity(0); Intake.moveVelocity(000); OutTake.moveVelocity(000);
  chassis->driveToPoint({2.2_ft, -1.7_ft});
  Roller.moveVelocity(0); Intake.moveVelocity(500); OutTake.moveVelocity(600);
  pros::delay(500);
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
  
  chassis->driveToPoint({0_ft, 0_ft}, true);
  // Roller.moveVelocity(200); Intake.moveVelocity(500);
  // chassis->driveToPoint({3_ft, 4_ft});
  // pros::delay(200);
  // Roller.moveVelocity(200); Intake.moveVelocity(0);
  // chassis->driveToPoint({6_ft, 1_ft});
  // chassis->driveToPoint({6_ft, 3_ft});
  // Roller.moveVelocity(0); Intake.moveVelocity(600); OutTake.moveVelocity(600);
  // chassis->driveToPoint({6_ft, 0_ft});
}

void blueSafe() {
  Roller.moveVelocity(200); Intake.moveVelocity(500); OutTake.moveVelocity(200);
  while (TopBallDetector.get() > 100 || TopBallDetector.get() == -1) {
    pros::delay(20);
  }
  OutTake.moveVelocity(0);
  chassis->moveDistance(1.7_ft);
  chassis->turnAngle(137_deg);
  Roller.moveVelocity(0); Intake.moveVelocity(000); OutTake.moveVelocity(000);
  chassis->moveDistance(2.1_ft);
  Roller.moveVelocity(0); Intake.moveVelocity(500); OutTake.moveVelocity(600);
  pros::delay(500);
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);

  chassis->moveDistance(-1.2_ft);
  chassis->turnAngle(-135_deg);
  Roller.moveVelocity(200); Intake.moveVelocity(300); OutTake.moveVelocity(400);
  while (TopBallDetector.get() > 100 || TopBallDetector.get() == -1) {
    pros::delay(20);
  }
  OutTake.moveVelocity(0);
  chassis->moveDistance(4_ft);
  while (BottomBallDetector.get() > 100 || BottomBallDetector.get() == -1) {
    pros::delay(20);
  }
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
  chassis->turnAngle(95_deg);
  chassis->moveDistance(0.6_ft);
  Roller.moveVelocity(0); Intake.moveVelocity(500); OutTake.moveVelocity(500);
  pros::delay(1400);
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
  
  chassis->moveDistance(-1.8_ft);
  chassis->turnAngle(-99_deg);
  Roller.moveVelocity(200); Intake.moveVelocity(400); OutTake.moveVelocity(300);
  chassis->moveDistance(4_ft);
  while (TopBallDetector.get() > 100 || TopBallDetector.get() == -1) {
    pros::delay(20);
  }
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
  chassis->turnAngle(68_deg);
  chassis->moveDistance(2.1_ft);
  Roller.moveVelocity(0); Intake.moveVelocity(500); OutTake.moveVelocity(500);
  pros::delay(600);
  chassis->moveDistance(-2_ft);
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
}

void blueLarge() {
  chassis->setState({0_in, 0_in, 0_deg});
  chassis->driveToPoint({3_ft, 0_ft});
  chassis->driveToPoint({0_ft, 0_ft});
}

void redSmall() {
}

void redLarge() {
}

void Skills () {
}

void redSafe() {
}


// Part of the auton selector code
void (*scripts[])() = {&redLarge, &redSmall, &blueLarge, &blueSmall};
void LCDScriptExecute() { scripts[selectedAuton - 1](); }
void autonomous() {
  isAuton = true;
  lv_tabview_set_tab_act(tabview, 2, true);
  
  switch (selectedAuton) {
    case 1: blueSmall();
      break;
    case 2: blueSafe();
      break;
    case 3: blueLarge();
      break;
    case 4: Skills();
      break;
    case 5: redLarge();
      break;
    case 6: redSafe();
      break;
    case 7: redSmall();
      break;
  }
  isAuton = false;
}