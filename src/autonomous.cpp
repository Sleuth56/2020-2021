#include "main.h"

// When set to true driver code stops
bool isAuton = false;

void CycleBalls(int Number, int Speed = 500) {
  Intake.moveVelocity(600); OutTake.moveVelocity(Speed);
  int a = 1;
  for (int i = 0; i < Number; ++i) {
    // Continues if ball
    while (TopBallDetector.get() > 50) {
      if (a > 100) {break;}
      pros::delay(20);
      a = a+1;
    }
    printf("Got Ball");
    a = 1;
    // if (i == 1){Intake.moveVelocity(0);}
    // Continues if no ball
    while (TopBallDetector.get() < 50) {
      if (a > 100) {break;}
      pros::delay(20);
      a = a+1;
    }
    printf("Released Ball");
    a = 1;
  }
  Intake.moveVelocity(0); 
  OutTake.moveVelocity(0);
}

bool stopBallAtTop = false;
bool stopBallAtBottom = false;
void intakeController(void* param) {
  while (true) {
    if (stopBallAtTop == true) {
      Roller.moveVelocity(200); Intake.moveVelocity(400); OutTake.moveVelocity(330);
      while (TopBallDetector.get() > 30) {
        if (stopBallAtTop == false) {break;}
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
      while (BottomBallDetector.get() > 80) {
        if (stopBallAtBottom == false) {break;}
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
  CycleBalls(1);
  pros::delay(20000);
}

void redSmall() {
}

void redLarge() {
}

// field 141_in
void Skills () {
  stopBallAtTop = true;
  pros::delay(800);
  chassis->setState({1.5_in, 105.75_in, 0_deg});
  stopBallAtBottom = true;
  chassis->driveToPoint({22.5_in, 105.75_in});

  // Put ball in the corner goal
  chassis->driveToPoint({7.4_in, 126_in});
  CycleBalls(1, 300);

  // Pickup second ball
  chassis->driveToPoint({15_in, 116_in}, true);
  stopBallAtTop = true;
  pros::delay(300);
  stopBallAtBottom = true;
  chassis->driveToPoint({43.1_in, 73_in});
  pros::delay(300);
  stopBallAtBottom = false;
  stopBallAtTop = false;
  chassis->driveToPoint({14.5_in, 72.5_in});
  CycleBalls(2);
  chassis->driveToPoint({23_in, 72_in}, true);

  // Third goal
  stopBallAtBottom = true;
  chassis->driveToPoint({22_in, 24_in});
  stopBallAtBottom = false;
  chassis->driveToPoint({13_in, 15.2_in});
  CycleBalls(1);

  // forth goal
  chassis->driveToPoint({46_in, 49_in}, true);
  stopBallAtTop = true;
  chassis->driveToPoint({67_in, 54_in});
  stopBallAtBottom = true;
  chassis->driveToPoint({69_in, 25.5_in});
  stopBallAtTop = false;
  stopBallAtBottom = false;
  Roller.moveVelocity(0);
  CycleBalls(2);
  chassis->driveToPoint({69_in, 35_in}, true);

  stopBallAtBottom = true;
  chassis->driveToPoint({118_in, 59_in});
  chassis->driveToPoint({90_in, 45_in}, true);
  stopBallAtBottom = false;
  chassis->driveToPoint({140_in, 10_in});
  CycleBalls(1);

  chassis->moveDistanceAsync(2_in);
  Roller.moveVelocity(200); Intake.moveVelocity(600); OutTake.moveVelocity(-600);
  while (BottomBallDetector.get() > 70) {
    pros::delay(20);
  }
  while (BottomBallDetector.get() < 70) {
    pros::delay(20);
  }
  chassis->moveDistance(-1_ft);
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
  // lv_tabview_set_tab_act(tabview, 2, true);
  
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