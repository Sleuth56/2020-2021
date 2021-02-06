#include "main.h"

// When set to true driver code stops
bool isAuton = false;
bool waitingForBall = false;

void stopForBall(void* param) {
  while (true) {
    if (waitingForBall == true && BottomBallDetector.get() < 100) {
      Intake.moveVelocity(0);
      waitingForBall = false;
    }
    pros::delay(20);
  }
}

void waitTillClear() {
    while (true) {
    if (TopBallDetector.get() > 100 && BottomBallDetector.get() > 100) {
      break;
    }
    pros::delay(20);
  }
}

void moveDistance(okapi::QLength distance, int timeout) {
     chassis->moveDistanceAsync(distance); // move to the target asynchronously (without waiting)
     long endTime = pros::millis() + timeout; // determine when to stop if it hasnt settled
     while(!chassis->isSettled()) { // loop if not settled
          if(pros::millis() >= endTime) { // if not settled and time has ran out
              chassis->stop();
               break; // break the loop and continue with autonomous
          }
     }
}

pros::Task stopForBall_TR(stopForBall, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "My Task");

void blueSmall() {
  // Roller.moveVelocity(200); Intake.moveVelocity(400);
  // waitingForBall = true;

  // // set the state to zero
  // chassis->setState({0_in, 0_in, 0_deg});
  // Roller.moveVelocity(200); Intake.moveVelocity(500);
  // chassis->driveToPoint({1.5_ft, 0_ft});
  // // pros::delay(200);
  // Roller.moveVelocity(0); Intake.moveVelocity(000); OutTake.moveVelocity(000);
  // chassis->driveToPoint({2.2_ft, -1.7_ft});
  // Roller.moveVelocity(0); Intake.moveVelocity(500); OutTake.moveVelocity(600);
  // pros::delay(500);
  // Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
  
  // chassis->driveToPoint({0_ft, 0_ft}, true);
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
  Roller.moveVelocity(200); Intake.moveVelocity(600); OutTake.moveVelocity(200);
  while (TopBallDetector.get() > 100 || TopBallDetector.get() == -1) {
    pros::delay(20);
  }
  OutTake.moveVelocity(0);
  waitingForBall = true;
  chassis->moveDistance(1.7_ft);
  Roller.moveVelocity(0); OutTake.moveVelocity(0);  
  chassis->turnAngle(132_deg);
  moveDistance(2.3_ft, 2300);
  Intake.moveVelocity(600); OutTake.moveVelocity(600);
  pros::delay(600);
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);

  chassis->moveDistance(-1.2_ft);
  chassis->turnAngle(-129_deg);
  Roller.moveVelocity(200); Intake.moveVelocity(600); OutTake.moveVelocity(200);
  while (TopBallDetector.get() > 100 || TopBallDetector.get() == -1) {
    pros::delay(20);
  }
  OutTake.moveVelocity(0);
  chassis->moveDistance(4.2_ft);
  pros::delay(550);
  Roller.moveVelocity(0); OutTake.moveVelocity(0); Intake.moveVelocity(0);
  chassis->turnAngle(93_deg);
  Roller.moveVelocity(0);
  moveDistance(1_ft, 2000);
  Roller.moveVelocity(200); Intake.moveVelocity(500); OutTake.moveVelocity(500);
  waitTillClear();
  Roller.moveVelocity(0);
  pros::delay(2000);
  Roller.moveVelocity(-200); Intake.moveVelocity(0); OutTake.moveVelocity(0);
  
  chassis->moveDistance(-1.8_ft);
  Roller.moveVelocity(0);
  chassis->turnAngle(-88_deg);
  Roller.moveVelocity(200); Intake.moveVelocity(300); OutTake.moveVelocity(200);
  chassis->moveDistance(4_ft);
  int timeout = pros::millis() + 10000;
  while (TopBallDetector.get() > 100 && timeout > pros::millis()) {
    pros::delay(20);
  }
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
  chassis->turnAngle(64_deg);
  moveDistance(2.5_ft, 3000);
  Roller.moveVelocity(0); Intake.moveVelocity(500); OutTake.moveVelocity(500);
  while (TopBallDetector.get() > 100 || BottomBallDetector.get() > 100) {
    pros::delay(20);
  }
  pros::delay(1000);
  chassis->moveDistance(-2_ft);
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);

  chassis->turnAngle(-157_deg);
  Roller.moveVelocity(200); Intake.moveVelocity(600);
  waitingForBall = true;
  chassis->moveDistance(6_ft);
  chassis->turnAngle(44_deg);
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
  moveDistance(2_ft, 2000);
  Roller.moveVelocity(200); Intake.moveVelocity(600); OutTake.moveVelocity(600);
  pros::delay(2000);
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