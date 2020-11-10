#include "main.h"
#pragma once

extern Controller master;

extern pros::ADIUltrasonic TopBallDetector;
extern pros::ADIUltrasonic BottomBallDetector;

extern okapi::Motor RightRollerMotor;
extern okapi::Motor LeftRollerMotor;
extern okapi::Motor Intake;
extern okapi::Motor OutTake;
extern okapi::MotorGroup Roller;