// Sanity Check To Prevent Double Inclusion
#ifndef ROBOT_H
#define ROBOT_H

// Needed To Define Lemlib Chassis And PROS Features
#include "main.h"
#include "lemlib/api.hpp"

// Declare All Variables Needed For Driver Control, Autonamous, And LVGL 
extern bool autonamous_left;
extern bool autonamous_right;
extern bool autonamous_skills;

// All Motors Used On The Robot Are Declared Here
extern pros::Controller master;
extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;
extern pros::Motor Rotate_Intake_Front;
extern pros::Motor Rotate_Intake_Back_And_Track;
extern pros::Motor Rotate_Tongue_Mech;
extern pros::Motor Rotate_TopGoalMech_One;
extern pros::Motor Rotate_TopGoalMech_Two;

extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;

void InitLemLib(void);

#endif