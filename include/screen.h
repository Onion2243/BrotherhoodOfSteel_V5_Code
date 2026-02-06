
// Essentially a Guard To Prevent Double Inclusion
#ifndef BROTHERHOOD_SCREEN_H // Named BROTHERHOOD_SCREEN_H To Avoid Conflicts With PROS SCREEN_H
#define BROTHERHOOD_SCREEN_H

#include "pros/apix.h"

void InitBrainScreen();
void UpdateScreen();
extern "C" {
    extern const lv_img_dsc_t Battery;
}


#endif