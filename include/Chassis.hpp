#include "main.h"
#pragma once

extern RotationSensor leftEncoder;
extern RotationSensor rightEncoder;

extern Motor frontLeftMotor;
extern Motor backLeftMotor;
extern Motor frontRightMotor;
extern Motor backRightMotor;
extern std::shared_ptr<OdomChassisController> chassis;
// extern std::shared_ptr<okapi::SkidSteerModel> driveTrain;

extern void ChassisOpcontrol(void* param);