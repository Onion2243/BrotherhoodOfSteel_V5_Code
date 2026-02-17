#include "robot.h"

void RunDriverControl()
{
    // Runs Constantly During Driver Control
	while (true) {

		// Gets The Left And Right Joystick Values From The Master Controller
		int leftJoystick_Y = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int rightJoystick_X = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick

		Descoring_Piston_Bottom.set_value(true); // Extends The Bottom Descoring Piston To Hold The Descoring Mechanism In The Correct Place

        // Uses LemLibs Arcade Drive Function To Control The Robot
		chassis.arcade(leftJoystick_Y, rightJoystick_X); 

		// Intake/Outtake Control
		if (master.get_digital(DIGITAL_R1)) { // If B Is Pressed, Run The Intake
			Rotate_Intake_And_Belt_Motor_One.move(127); // Runs The First Intake Motor Forward
			Rotate_Intake_And_Belt_Motor_Two.move(-127); // Runs The Second Intake Motor Forward
		} else if (master.get_digital(DIGITAL_R2)) { // If A Is Pressed, Run The Outtake
			Rotate_Intake_And_Belt_Motor_One.move(-127); // Runs The First Intake Motor Backward
			Rotate_Intake_And_Belt_Motor_Two.move(127); // Runs The Second Intake Motor Backward
		} else { // If Neither Are Pressed, Stop The Intake/Outtake Motors
			Rotate_Intake_And_Belt_Motor_One.move(0); // Stops The First Intake Motor
			Rotate_Intake_And_Belt_Motor_Two.move(0); // Stops The Second Intake Motor
		}

		// Outtake Piston Control
		if (master.get_digital(DIGITAL_L1)) { // If L1 Is Pressed, Extend The Outtake Piston
			Outtake_Piston.set_value(false); // Extends The Outtake Piston
		} else if (master.get_digital(DIGITAL_L2)) { // If L2 Is Pressed, Retract The Outtake Piston
			Outtake_Piston.set_value(true); // Retracts The Outtake Piston
		}


		// Descorering Piston Control
		if (master.get_digital(DIGITAL_RIGHT))
		{
			Descoring_Piston_Top.set_value(true); // Extends The Descoring Piston
		} 
		else if (master.get_digital(DIGITAL_DOWN)) 
		{
			Descoring_Piston_Top.set_value(false); // Retracts The Descoring Piston
		}

		// Matchloader Control
		if (master.get_digital(DIGITAL_Y)) {
			Rotate_Matchloader.move(127); // Runs The Matchloader Motor Forward
		} else if (master.get_digital(DIGITAL_B)) {
			Rotate_Matchloader.move(-127); // Runs The Matchloader Motor Backward
		} else {
			Rotate_Matchloader.move(0); // Stops The Matchloader Motor
		}
		// Run for 20 ms then update
		pros::delay(20);
	}
}