// Includes All PROS Header And C++ Files
#include "main.h"
#include "autonamous.h"
#include "screen.h"
#include "robot.h"
#include "driver.h"


// Runs Initialization Code. This Function Runs Once The Program Is Started
void initialize() 
{
	InitBrainScreen(); // Initalizes The Brain Screen For LVGL
	UpdateScreen(); // Updates The Brain Screen
	InitLemLib(); // Initializes LemLib
}


// Runs During The Autonamous Period Of The Round
void autonomous() 
{
	chassis.calibrate(); // Calibrates The Inertial Sensor At The Start Of Autonamous
	chassis.setPose(0, 0, 0); // Sets The Initial Pose Of The Robot To (0, 0) With A Heading Of 0 Degrees
	RunSelectedAutonamous(); // Gets The Selected Autonamous And Runs It
}

// Runs During The One Minute 45 Second Driver Control Period Of The Match
void opcontrol() {
	RunDriverControl(); // Runs The Driver Control Code
}