#include "main.h"
#include "robot.h"

// Define Autonamous Variables
bool autonamous_left = true;
bool autonamous_right = false;
bool autonamous_skills = false;

// All Motors Used On The Robot Are Declared Here
pros::Controller master(pros::E_CONTROLLER_MASTER); // Creates The Master Controller
pros::MotorGroup left_mg({-10, 6, -20}, pros::MotorGearset::blue);    // Creates a motor group with forwards ports -11 & -20 and reversed port 2
pros::MotorGroup right_mg({11, -5, 3}, pros::MotorGearset::blue);  // Creates a motor group with forwards port 5 and reversed ports 1 & 10
pros::Motor Rotate_Intake_And_Belt_Motor_One (19); // Creates A Motor On Port 20 For Rotating The Front Intake
pros::Motor Rotate_Intake_And_Belt_Motor_Two (12); // Creates A Motor On Port 19 Which Rotates The Back Intake And The Belt
pros::Motor Rotate_Matchloader (5); // Creates A Motor On Port 15 Which Rotates The Matchloader

// All Pneumatics Used On The Robot Are Declared Here
pros::ADIDigitalOut Outtake_Piston('A'); // Creates The Outtake Piston On Port A
pros::ADIDigitalOut Descoring_Piston_Top('B'); // Creates The Descoring Piston On Port B
pros::ADIDigitalOut Descoring_Piston_Bottom('G'); // Creates The Descoring Piston On Port C

pros::Imu Inertial_Sensor(1); // Creates The Inertial Sensor On Port 7

// Drivetrain Configuration For LemLib Chassis
lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg,// right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// Odometry Sensors Configuration For LemLib Chassis
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to nullptr
                            nullptr, // vertical tracking wheel 2, set to nullptr 
                            nullptr, // horizontal tracking wheel 1, set to nullptr
                            nullptr, // horizontal tracking wheel 2, set to nullptr
                            &Inertial_Sensor // inertial sensor
);

// Lateral PID Controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// Angular PID Controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// Defining The Chassis Object Using The Above Configurations
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

// Initalizes LemLib
void InitLemLib()
{
    chassis.calibrate(); // Calibrate The Chassis
    chassis.setPose(0, 0, 0); // Set Starting Pose
}