#include "robot.h"

void RunDriverControl()
{
    // Runs Constantly During Driver Control
	while (true) {

		// Gets The Left And Right Joystick Values From The Master Controller
		int leftJoystick = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int rightJoystick = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick

        // Uses LemLibs Arcade Drive Function To Control The Robot
		chassis.arcade(leftJoystick, rightJoystick); 

		// Run for 20 ms then update
		pros::delay(20);
	}
}