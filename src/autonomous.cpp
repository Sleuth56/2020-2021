#include "main.h"

// When set to true driver code stops
bool isAuton = false;

void CycleBalls(int Number = 1, int Speed = 500) {
  Intake.moveVelocity(600); OutTake.moveVelocity(Speed);
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

bool stopBallAtTop = false;
bool stopBallAtBottom = false;
void intakeController(void* param) {
  while (true) {
    if (stopBallAtTop == true) {
      Roller.moveVelocity(200); Intake.moveVelocity(600); OutTake.moveVelocity(60);
      while (TopBallDetector.get() > 30 || TopBallDetector.get() == 0) {
          pros::delay(20);
      } 
      // while (BottomBallDetector.get() < 170 || BottomBallDetector.get() == 0) {
      //     pros::delay(20);
      // }
      Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
      stopBallAtTop = false;
    }
    if (stopBallAtBottom == true) {
      Roller.moveVelocity(200); Intake.moveVelocity(600);
      while (BottomBallDetector.get() > 80 || BottomBallDetector.get() == 0) {
        pros::delay(20);
      }
      Roller.moveVelocity(0); Intake.moveVelocity(0); OutTake.moveVelocity(0);
      stopBallAtBottom = false;
    }
    pros::delay(30);
  }
}

pros::Task intakeController_TR(intakeController, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "My Task");

void blueSmall() {
}

void blueSafe() {
}

void blueLarge() {
  stopBallAtBottom = true;
  pros::delay(20000);
}

void redSmall() {
}

void redLarge() {
}

// field 141_in
void Skills () {
  chassis->setState({9_in, 129_in, 120_deg});
  // Put ball in the corner goal
  chassis->driveToPoint({6.746_in, 132_in});
  // CycleBalls(1);
  CycleBalls(1, 300);

  // Pickup second ball
  chassis->driveToPoint({11_in, 126_in}, true);
  stopBallAtTop = true;
  chassis->driveToPoint({23_in, 105.75_in});
  stopBallAtBottom = true;
  chassis->driveToPoint({46_in, 80_in});
  chassis->driveToPoint({11.5_in, 80.5_in});
  CycleBalls(2);
  chassis->driveToPoint({21_in, 80_in}, true);

  // Third goal
  stopBallAtBottom = true;
  chassis->driveToPoint({19_in, 35_in});
  chassis->driveToPoint({9_in, 24_in});
  CycleBalls(1);

  // forth goal
  chassis->driveToPoint({46_in, 47_in}, true);
  stopBallAtTop = true;
  chassis->driveToPoint({75_in, 47_in});
  stopBallAtBottom = true;
  chassis->driveToPoint({75_in, 23.25_in});
  chassis->driveToPoint({75_in, 10_in});
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