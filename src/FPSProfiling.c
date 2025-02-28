
#include "../include/FPSProfiling.h"



void updateFPSTracker(int sampleTime, int exit) {
	double elapsedTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	numFrames++;
	//printf("\nTime Since Last Frame: %.8f", 1.0f/elapsedTime);
	if (glfwGetTime() - checkTime > 1) {
		printf("\n%.2f", numFrames);
		checkTime = glfwGetTime();
		if (frameChecks >= sampleTime) {
			frameChecks = 0;
			double avg = 0;
			for (int i = 0; i < sampleTime; i++) {
				avg += frameRates[i];
			}
			printf("\nAverage FPs over %d seconds : %.2f FPS", sampleTime, avg / (float)sampleTime);
			if (exit == 1) {
				quick_exit(0);
			}
		}
		else {
			frameRates[frameChecks] = numFrames;
			frameChecks++;
		}

		numFrames = 0;
	}
}
