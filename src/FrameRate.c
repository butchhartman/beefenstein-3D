#include "FrameRate.h"

int sampleCount = 5;

double lastTime = 0.0f;

double *FPS;

void FrameRate_init() {
	FPS = (double*)calloc(sampleCount, sizeof(double));
}

void FrameRate_updateCount()
{
	const double now = ((double)SDL_GetTicks()) / 1000.0f; // converts from ms to s

	FPS[(int)now % sampleCount] = 1.0f / (now - lastTime);

	lastTime = now;
}

double FrameRate_calculateAverageFPS()
{
	double avg = 0;
	for (int i = 0; i < sampleCount; i++) {
		avg += FPS[i];
	}
	avg /= sampleCount;
	return avg;
}

void FrameRate_printAverageFPS()
{
	printf("Average FPS : %.2f \n", FrameRate_calculateAverageFPS());
}

void FrameRate_setSampleCount(int count) {
	sampleCount = count;
}

void FrameRate_cleanUp() {
	free(FPS);
}