// Includes All PROS Header And C++ Files
#include "main.h"
#include "autonamous.h"
#include "screen.h"
#include "robot.h"


// Runs Initialization Code. This Function Runs Once The Program Is Started
void initialize() 
{
	InitBrainScreen(); // Initalizes The Brain Screen For LVGL
	UpdateScreen(); // Updates The Brain Screen
	InitLemLib(); // Initalizes LemLib
}


// Runs During The Autonamous Period Of The Round
void autonomous() 
{
	RunSelectedAutonamous();	
}

// Runs During The One Minute 45 Second Driver Control Period Of The Match
void opcontrol() {
	// Runs Constantly During Driver Control
	while (true) {

		// This Is A Arcade Style Drive Control Setup.
		int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick

		chassis.arcade(dir, turn); // Uses LemLibs Arcade Drive Function To Control The Robot

		Rotate_Tongue_Mech.set_brake_mode(MOTOR_BRAKE_HOLD); // Sets The Tongue Mechanism Motor To HOLD Mode So It Doesn't Fall Due To Gravity


		// Parking Brake Functionality
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) 			   // Checks To See If Button A On The Controller Is Being Pressed
		{
			left_mg.set_brake_mode(MOTOR_BRAKE_BRAKE);  // Sets The Braking Mode Of The Right Motor Group To BRAKE
			right_mg.set_brake_mode(MOTOR_BRAKE_BRAKE); // Sets The Braking Mode Of The Right Motor Group To BRAKE

			left_mg.brake();							// Makes The Left Motor Group Brake
			right_mg.brake();							// Makes The Right Motor Group Brake
		}
		else										// If Button A Is Not Being Pressed
		{
			left_mg.set_brake_mode(MOTOR_BRAKE_COAST);  // Sets The Braking Mode Of The Left Motor Group To COAST
			right_mg.set_brake_mode(MOTOR_BRAKE_COAST); // Sets The Braking Mode Of The Right Motor Group To COAST
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) // Checks To See If Button R1 On The Controller Is Being Pressed
		{
			Rotate_Intake_Front.move(127); // Sets The Intake Motor Front To Full Speed Forward
			Rotate_Intake_Back_And_Track.move(-127); // Sets The Intake Motor Back To Full Speed Forward

		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) // Checks To See If Button R2 On The Controller Is Being Pressed
		{
			Rotate_Intake_Front.move(-127); // Sets The Intake Motor Front To Full Speed Backward
			Rotate_Intake_Back_And_Track.move(127); // Sets The Intake Motor Back To Full Speed Backward
		}
		else
		{
			Rotate_Intake_Front.move(0); // Stops The Intake Motor Front
			Rotate_Intake_Back_And_Track.move(0); // Stops The Intake Motor Back
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) // Checks To See If Button Down On The Controller Is Being Pressed
		{
			Rotate_Tongue_Mech.move(100); // Sets The Slider Piston State To Extended
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) // Checks To See If Button Right On The Controller Is Being Pressed
		{
			Rotate_Tongue_Mech.move(-40); // Sets The Slider Piston State To Retracted
		}
		else
		{
			Rotate_Tongue_Mech.move(0); // Stops The Slider Piston Motor
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) // Checks To See If Button L1 On The Controller Is Being Pressed
		{
			Rotate_TopGoalMech_One.move(127); // Sets The Intake Motor Front To Full Speed Forward
			Rotate_TopGoalMech_Two.move(-127); // Sets The Intake Motor Back To Full Speed Forward

		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) // Checks To See If Button L2 On The Controller Is Being Pressed
		{
			Rotate_TopGoalMech_One.move(-127); // Sets The Intake Motor Front To Full Speed Backward
			Rotate_TopGoalMech_Two.move(127); // Sets The Intake Motor Back To Full Speed Backward
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) // Checks To See If Button X On The Controller Is Being Pressed
		{
			Rotate_TopGoalMech_One.move(-127); // Sets The Intake Motor Front To Speed Forward
			Rotate_TopGoalMech_Two.move(0); // Sets The Intake Motor Back To Stop
		}
		else
		{
			Rotate_TopGoalMech_One.move(0); // Stops The Intake Motor Front
			Rotate_TopGoalMech_Two.move(0); // Stops The Intake Motor Back
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) // Checks To See If Button B On The Controller Is Being Pressed
		{
			chassis.moveToPoint(10, 10, 10); // move to point (10, 10) with a timeout of 4000 ms
		}

		// Run for 20 ms then update
		pros::delay(20);
	}
}