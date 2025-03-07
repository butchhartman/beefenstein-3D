#include "FrameRate.h"

int sampleCount = 5;

Uint64 lastTime = 0.0f;

double deltaTime = 0.0f;

double *FPS;

void FrameRate_init() {
	FPS = (double*)calloc(sampleCount, sizeof(double));
}

void FrameRate_updateCount()
{
	const Uint64 now = SDL_GetPerformanceCounter(); 
	deltaTime = (double)(((now - lastTime)) / ((double)SDL_GetPerformanceFrequency()));
	FPS[(int)(SDL_GetTicks()/1000.0f) % sampleCount] = 1.0 / deltaTime;

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
	printf("Average FPS : %.20f \n", FrameRate_calculateAverageFPS());
}

void FrameRate_setSampleCount(int count) {
	sampleCount = count;
}

void FrameRate_cleanUp() {
	free(FPS);
}

double FrameRate_getDeltaTime()
{
	return deltaTime;
}
