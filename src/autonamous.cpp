// Includes All PROS Header And C++ Files
#include "robot.h"
#include "autonamous.h"

// Runs Autonamous For The Left Side Of The Field
void AutonamousLeft()
{
    Descoring_Piston_Bottom.set_value(true); // Extends The Bottom Descoring Piston To Hold The Descoring Mechanism In The Correct Place
	Descoring_Piston_Top.set_value(true); // Extends The Top Descoring Piston To Hold The Descoring Mechanism In The Correct Place
}

// Runs Autonamous For The Right Side Of The Field
void AutonamousRight()
{
	Descoring_Piston_Bottom.set_value(true); // Extends The Bottom Descoring Piston To Hold The Descoring Mechanism In The Correct Place
	Descoring_Piston_Top.set_value(true); // Extends The Top Descoring Piston To Hold The Descoring Mechanism In The Correct Place


    chassis.moveToPoint(0, 24, 500); // Move Forward 24 Inches
    Rotate_Intake_And_Belt_Motor_One.move(127); // Runs The First Intake Motor Forward To Intake The First Two Disks
    Rotate_Intake_And_Belt_Motor_Two.move(-127); // Runs The Second Intake Motor Forward To Intake The First Two Disks
    pros::delay(1000); // Delay For 1 Second To Ensure The Disks
    chassis.moveToPoint(0, 18, 500); // Move Backwards 24 Inches To The Starting Position
    chassis.turnToHeading(90, 500); // Turn 90 Degrees To The Right
    chassis.moveToPoint(24, 0, 500); // Move Right 24 Inches To The Goal
}

// Runs The Autonamous For Skills
void AutonamousSkills()
{
    Descoring_Piston_Bottom.set_value(true); // Extends The Bottom Descoring Piston To Hold The Descoring Mechanism In The Correct Place
	Descoring_Piston_Top.set_value(true); // Extends The Top Descoring Piston To Hold The Descoring Mechanism In The Correct Place
}

// Will Run Autonamous Depending On What Has Been Selected On Which Autonamous Variable Is True
void RunSelectedAutonamous()
{
    if (AUTON_LEFT == true)
    {
        AutonamousLeft();
    }
    else if (AUTON_RIGHT == true)
    {
        AutonamousRight();
    }
    else if (AUTON_SKILLS == true)
    {
        AutonamousSkills();
    }
}