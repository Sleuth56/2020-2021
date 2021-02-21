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

void CycleBalls(int Number = 1) {
  // Roller.moveVelocity(200); 
  Intake.moveVelocity(600); OutTake.moveVelocity(600);
  int a = 1;
  for (int i = 1; i <= Number; ++i) {
    while (TopBallDetector.get() > 100 || TopBallDetector.get() == -1) {
      if (a > 60) {break;}
      pros::delay(20);
      a = a+1;
    }
    a = 1;
    while (TopBallDetector.get() < 100 || TopBallDetector.get() == -1) {
      if (a > 60) {break;}
      pros::delay(20);
      a = a+1;
    }
    a = 1;
  }
  Intake.moveVelocity(0); 
  pros::delay(700);
  OutTake.moveVelocity(0);
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

// pros::Task stopForBall_TR(stopForBall, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "My Task");

void blueSmall() {
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
// Position State check.
// Should end up at the close center ball in between the middle goals
void blueLarge() {
  chassis->setState({1.3_ft, 9_ft, 0_deg});
  chassis->turnToPoint({1.3_ft, 15_ft});
}

void redSmall() {
}

void redLarge() {
}

void Skills () {
  chassis->setState({1.3_ft, 9_ft, 0_deg});
  int a = 0;
  // Ball to top roller
  Roller.moveVelocity(200); Intake.moveVelocity(600); OutTake.moveVelocity(50);
  while (BottomBallDetector.get() > 80 || BottomBallDetector.get() == -1) {
    if (a > 40) {break;}
    pros::delay(20);
    a = a+1;
  }
  a = 0;
  // pros::delay(200);
  Intake.moveVelocity(200);
  
  // Get first ball
  chassis->driveToPoint({3.23_ft, 8.9_ft});
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);

  // Put ball in the corner goal
  chassis->driveToPoint({1.7_ft, 10.6_ft});
  CycleBalls(1);

  // Get second ball
  OutTake.moveVelocity(-50);
  chassis->driveToPoint({5.1_ft, 8.4_ft}, true);
  chassis.get()->setMaxVelocity(50);
  Roller.moveVelocity(200); Intake.moveVelocity(600); OutTake.moveVelocity(50);
  chassis->driveToPoint({5.1_ft, 6.45_ft});
  while (BottomBallDetector.get() > 80 || BottomBallDetector.get() == -1) {
    if (a > 40) {break;}
    pros::delay(20);
    a = a+1;
  }
  a = 0;
  OutTake.moveVelocity(0); Roller.moveVelocity(0); Intake.moveVelocity(0);
  chassis.get()->setMaxVelocity(75);

  // Two balls in home center goal
  chassis->driveToPoint({2.5_ft, 6_ft});
  CycleBalls(1);

  // Get third ball
  chassis.get()->setMaxVelocity(40);
  chassis->driveToPoint({3_ft, 6.2_ft}, true);
  chassis.get()->setMaxVelocity(75);
  Roller.moveVelocity(200); Intake.moveVelocity(400); OutTake.moveVelocity(50);
  chassis->driveToPoint({3.4_ft, 2.3_ft});
  while (BottomBallDetector.get() > 80 || BottomBallDetector.get() == -1) {
    if (a > 40) {break;}
    pros::delay(20);
    a = a+1;
  }
  a = 0;
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);

  // Drop into left home zone
  chassis->driveToPoint({3_ft, 1.4_ft});
  CycleBalls(1);

  // Get forth ball
  chassis.get()->setMaxVelocity(40);
  chassis->driveToPoint({3.7_ft, 2.7_ft}, true);
  chassis.get()->setMaxVelocity(75);
  Roller.moveVelocity(170); Intake.moveVelocity(600); OutTake.moveVelocity(50);
  chassis->driveToPoint({7.2_ft, 3.05_ft});
  while (BottomBallDetector.get() > 80 || BottomBallDetector.get() == -1) {
    if (a > 40) {break;}
    pros::delay(20);
    a = a+1;
  }
  a = 0;
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);

  // one ball in far middle tower
  chassis->driveToPoint({7.5_ft, 2.49_ft});
  CycleBalls(1);

  // get fith ball
  chassis.get()->setMaxVelocity(40); 
  chassis->driveToPoint({7.2_ft, 3.2_ft}, true);
  chassis.get()->setMaxVelocity(75);
  Roller.moveVelocity(170); Intake.moveVelocity(600); OutTake.moveVelocity(50);  
  chassis->driveToPoint({6.9_ft, 4.75_ft});
  while (BottomBallDetector.get() > 80 || BottomBallDetector.get() == -1) {
    if (a > 40) {break;}
    pros::delay(20);
    a = a+1;
  }
  a = 0;
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);

  // Put ball in far left goal
  chassis->driveToPoint({12_ft, 3.74_ft});
  Roller.moveVelocity(200);
  CycleBalls(1);
  Intake.moveVelocity(600); OutTake.moveVelocity(-600);
  while (BottomBallDetector.get() > 80 || BottomBallDetector.get() == -1) {
    pros::delay(20);
  }
  pros::delay(3000);
  chassis->driveToPoint({10_ft, 4_ft}, true);
  Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
}

void redSafe() {
}

int selectedAuton = 4;
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