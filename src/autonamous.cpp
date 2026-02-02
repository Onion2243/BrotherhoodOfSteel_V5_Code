// Includes All PROS Header And C++ Files
#include "main.h"
#include "robot.h"
#include "autonamous.h"

// Runs Autonamous For The Left Side Of The Field
void AutonamousLeft()
{

}

// Runs Autonamous For The Right Side Of The Field
void AutonamousRight()
{

}

// Runs The Autonamous For Skills
void AutonamousSkills()
{

}

// Will Run Autonamous Depending On What Has Been Selected On Which Autonamous Variable Is True
void RunSelectedAutonamous()
{
    if (autonamous_left == true)
    {
        AutonamousLeft();
    }
    else if (autonamous_right == true)
    {
        AutonamousRight();
    }
    else if (autonamous_skills == true)
    {
        AutonamousSkills();
    }
}