#pragma once

#include "../include/GLFW/glfw3.h"

// Globals. Bad Practice. Boo.
double lastTime;
double numFrames;
double checkTime;
double frameRates[10];
int frameChecks;


/*Tracks and prints the FPS every second for sampleTime seconds
Upon reaching sampleTime seconds, the program exits and the sampleTime second average is printed
If exit is true (1), the program will not quit after is average FPS is calculated
Otherwise, the function will continue to calculate average FPS every sampleTime seconds*/
void updateFPSTracker(int sampleTime, int exit);