// Includes Main, Screen, Robot, And PROS LVGL Header Files
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/widgets/lv_label.h"
#include "main.h"
#include "screen.h"
#include "robot.h"
#include "pros/apix.h"

// THIS IS PURELY FOR INTELLISENSE, IN ORDER FOR BUIDLING TO WORK IT MUST BE COMMENTED OUT
//#include "include/liblvgl/lvgl.h" 

// Variables 
char AutonResult[32]; // AutonResult Variable, Which Will Store The Selected Auton Mode As A String (Can Only Hold 32 Characters)
lv_obj_t * AutonChangedLabel = nullptr; // Creates The AutonChangedLabel
lv_obj_t * Battery_Arc = nullptr; // Creates The Battery Arc Object
lv_obj_t * Battery_Label = nullptr; // Creates The Battery Label Object


// Initalizes The Brain Screen To Work With LVGL
void InitBrainScreen()
{
    // Initialize LVGL
    lvgl_init();
}

// The Event Handler Function Handles All Events That Are Done Through The Screen, Such As Selected Auton Modes
void EventHandler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e); // Gets The Event Code, Such As Clicked, Pressed, Changed, Etc.
    lv_obj_t * target = lv_event_get_target(e); // Gets The Target Object That The Event Was Done On. E.g. The Auton Dropdown Menu
    
    // Run If The Event Code Was A Value Change
    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_dropdown_get_selected_str(target, AutonResult, sizeof(AutonResult)); // Gets The String From The Option The User Selected And Stores It To AutonResult
        char LabelBuffer[48]; // Buffer Variable To Hold The Full Label Text
        snprintf(LabelBuffer, sizeof(LabelBuffer), "Selected Auton: %s", AutonResult); // Formats The Full Label Text Into The Buffer Variable
        lv_label_set_text(AutonChangedLabel, LabelBuffer); // Updates The Label To Show The Selected Auton Mode

        // Sets Autonamous Variables Based On The Selected Auton Mode
        if (AutonResult == "Auton Left") {
            autonamous_left = true; // Sets The Selected Auton Mode To Auton Left
            autonamous_right = false; // Sets Autonamous Right To False
            autonamous_skills = false; // Sets Autonamous Skills To False
        } 
        else if (AutonResult == "Auton Right") {
            autonamous_left = false; // Sets Autonamous Left To False
            autonamous_right = true; // Sets Autonamous Right To True
            autonamous_skills = false; // Sets Autonamous Skills To False
        } 
        else if (AutonResult == "Auton Skills") {
            autonamous_left = false; // Sets Autonamous Left To False
            autonamous_right = false; // Sets Autonamous Right To False
            autonamous_skills = true; // Sets Autonamous Skills To True
        }
    }
}

// The BatteryTask Continuosely Updates The Battery Arc On The Screen To Reflect The Current Battery Level
void BatteryPercentage()
{
    // Runs Forever While The Program Is Running
    while (true) {
        int batteryLevel = pros::battery::get_capacity(); // Gets The Current Battery Level As A Percentage
        char batteryLevelString[32]; // Buffer Variable To Hold The Battery Level As A String
        snprintf(batteryLevelString, sizeof(batteryLevelString), "%d%%", batteryLevel); // Formats The Battery Level As A String With Percentage Sign

        // Update LVGL Objects
        lv_arc_set_value(Battery_Arc, batteryLevel); // Updates The Battery Arc To Reflect The Current Battery Level
        lv_label_set_text(Battery_Label, batteryLevelString); // Updates The Battery Label To Show The Current Battery Percentage

        // Delay To Prevent Program From Freezing
        pros::delay(500); // Delay For 1 Second Before Updating Again
    }
}

// This Function Will House All Of The Code For The Screen And Its Logic
void UpdateScreen()
{   
    // Auton Dropdown Menu
    lv_obj_t * AutonDropDown = lv_dropdown_create(lv_scr_act()); // Creates The Dropdown Menu On The Active Screen
    lv_dropdown_set_options(AutonDropDown, "Auton Left\nAuton Right\nAuton Skills"); // Sets The Options For The Dropdown Menu
    lv_obj_align(AutonDropDown, LV_ALIGN_TOP_RIGHT, -2, 2); // Aligns The AutonDropdown To The Top Right Of The Screen
    lv_obj_add_event_cb(AutonDropDown, EventHandler, LV_EVENT_ALL, NULL); // Creates The Event Callback For The Dropdown Menu

    // Auton Changed Label
    AutonChangedLabel = lv_label_create(lv_scr_act()); // Creates The AutonChangedLabel On The Active Screen
    lv_label_set_text(AutonChangedLabel, "No Auton Selected"); // Updates The Label To Show The Selected Auton Mode
    lv_obj_align(AutonChangedLabel, LV_ALIGN_BOTTOM_MID, 0, -4); // Aligns The Selected Auton Label To The Bottom Middle Of The Screen

    // Battery Arc
    Battery_Arc = lv_arc_create(lv_scr_act()); // Creates The Battery Arc On The Active Screen
    lv_obj_set_size(Battery_Arc, 100, 100); // Sets The Size Of The Battery Arc To 50x50 Pixels
    lv_arc_set_rotation(Battery_Arc, 135); // Sets The Rotation Of The Arc To 180 By Default
    lv_arc_set_bg_angles(Battery_Arc, 0, 270); // Sets The Maximum Angle Of The Arc To 270 Degrees
    lv_arc_set_range(Battery_Arc, 0, 100); // Sets The Range Of Values For The Arc Between 0 And 100
    lv_obj_remove_style(Battery_Arc, NULL, LV_PART_KNOB); // Removes The Knob Style From The Arc
    lv_obj_clear_flag(Battery_Arc, LV_OBJ_FLAG_CLICKABLE); // Stops The Arc From Being Clickable And Adjustable
    lv_obj_align(Battery_Arc, LV_ALIGN_TOP_LEFT, 5, 6); // Aligns The Arc To The Appropriate Position On The Screen

    // Battery Label
    Battery_Label = lv_label_create(lv_scr_act()); // Creates The Battery Label On The Active Screen
    lv_obj_align_to(Battery_Label, Battery_Arc, LV_ALIGN_BOTTOM_MID, 0, 3); // Aligns The Battery Label To The Bottom Middle Of The Battery Arc

    pros::Task BatteryPercentageTask(BatteryPercentage); // Starts The Battery Percentage Task To Continuosely Update The Battery Arc
}