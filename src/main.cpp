// Includes All PROS Header And C++ Files
#include "main.h"
#include "pros/adi.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep

// THIS IS PURELY FOR INTELLISENSE, IN ORDER FOR BUIDLING TO WORK IT MUST BE COMMENTED OUT
// #include "include/liblvgl/lvgl.h" 

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


// Declare All Variables Needed For Driver Control, Autonamous, And LVGL 
bool autonamous_left = true;
bool autonamous_right = false;


// Runs Initialization Code. This Function Runs Once The Program Is Started
void initialize() {
	
	// Initializes LVGL Setup And Screen Code
	lvgl_init();

	// Lemlib Chassis Configuration
	chassis.calibrate(); // Calibrate Sensors
	chassis.setPose(0, 0, 0); // Set Starting Pose
}

// Runs while the robot is in the disabled state of Field Management System or the VEX Competition Switch, following either 
// autonomous or opcontrol. When the robot is enabled, this task will exit.
void disabled() 
{

}

// Runs After Initialize BUT Before Autonamous
void competition_initialize() 
{
	pros::Controller master(pros::E_CONTROLLER_MASTER); // Creates The Master Controller
	master.clear(); // Clears The Controller Screen On Program Start
	
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) // Checks To See If Button X On The Controller Is Being Pressed
		{
			if (autonamous_left == false) // Checks To See If Neither Autonamous Left Or Right Has Been Selected
			{
				autonamous_left = true; // Sets Autonamous Left To True As Default
				autonamous_right = false; // Sets Autonamous Left To False

				master.print(1, 1, "Autonamous Left Selected"); // Prints To The Controller Screen That Autonamous Left Has Been Selected
				pros::delay(300); // Adds A Small Delay To Prevent Button Bouncing
				master.clear(); // Clears The Controller Screen

			}
			
			// Checks If Autonamous Left Is Enabled And Right Is Disabled. If So, It Switches Them
			if (autonamous_left == true && autonamous_right == false) // Checks To See If Autonamous Left Has Been Selected
			{
				autonamous_right = true; // Sets Autonamous Right To True
				autonamous_left = false; // Sets Autonamous Left To False

				master.print(1, 1, "Autonamous Right Selected"); // Prints To The Controller Screen That Autonamous Right Has Been Selected
				pros::delay(300); // Adds A Small Delay To Prevent Button Bouncing
				master.clear(); // Clears The Controller Screen
			}
		}

	pros::delay(20); // Small Delay For 20ms

}

// Runs During The Autonamous Period Of The Round
void autonomous() 
{
		if (autonamous_left == true && autonamous_right == false) // Checks To See If Autonamous Left Has Been Selected
		{
			// All Autonamous Left Code Goes Here
			chassis.moveToPose(0, 24, 0, 100); // move forward 24 inches

		}
		else if (autonamous_right == true && autonamous_left == false) // Checks To See If Autonamous Right Has Been Selected
		{
			// All Autonamous Right Code Goes Here

		}
		pros::delay(20); // Small Delay for 20ms
		
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