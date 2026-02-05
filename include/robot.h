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
extern pros::Motor Rotate_Intake_And_Belt_Motor_One;
extern pros::Motor Rotate_Intake_And_Belt_Motor_Two;
extern pros::Motor Rotate_Outtake_Gears;
extern pros::Motor Rotate_Matchloader;

// All Pneumatics Used On The Robot Are Declared Here
extern pros::ADIDigitalOut Descoring_Piston;
extern pros::ADIDigitalOut Outtake_Piston_One;
extern pros::ADIDigitalOut Outtake_Piston_Two;

// All Lemlib Objects Are Declared Here
extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;

// All Sensors Are Declared Here
extern pros::Imu Inertial_Sensor;

void InitLemLib(void);

#endif