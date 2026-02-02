#include "main.h"
#include "robot.h"

// Define Autonamous Variables
bool autonamous_left = false;
bool autonamous_right = false;
bool autonamous_skills = false;

// All Motors Used On The Robot Are Declared Here
pros::Controller master(pros::E_CONTROLLER_MASTER); // Creates The Master Controller
pros::MotorGroup left_mg({-11, 6, -12}, pros::MotorGearset::blue);    // Creates a motor group with forwards ports -11 & -20 and reversed port 2
pros::MotorGroup right_mg({13, -5, 14}, pros::MotorGearset::blue);  // Creates a motor group with forwards port 5 and reversed ports 1 & 10
pros::Motor Rotate_Intake_Front (20); // Creates A Motor On Port 20 For Rotating The Front Intake
pros::Motor Rotate_Intake_Back_And_Track (19); // Creates A Motor On Port 19 Which Rotates The Back Intake And The Track
pros::Motor Rotate_Tongue_Mech (1); // Creates A Motor On Port 17 Which Rotates The Tongue Mechanism
pros::Motor Rotate_TopGoalMech_One (15); // Creates A Motor On Port 15 Which Rotates Half Of The Top Goal Scoring Mechanism
pros::Motor Rotate_TopGoalMech_Two (16); // Creates A Motor On Port 16 Which Rotates The Other Half Of The Top Goal Scoring Mechanism

// Drivetrain Configuration For LemLib Chassis
lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg,// right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              360, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// Odometry Sensors Configuration For LemLib Chassis
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr // inertial sensor
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