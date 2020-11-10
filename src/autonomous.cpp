#include "main.h"

// When set to true driver code stops
bool isAuton = false;

void blueSmall() {
  // chassis->moveDistance(4_ft);
  // chassis->turnAngle(-90_deg);
  // chassis->moveDistance(2_ft);
  chassis->turnAngle(90_deg);
  // chassis->moveDistance(2_ft);
  // OutTake.moveVelocity(600);
  // chassis->turnToPoint(0, 1);
}

void blueLarge() {
}

void redSmall() {
}

void redLarge() {
}

void Skills () {
}

void redSafe() {
}

void blueSafe() {
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