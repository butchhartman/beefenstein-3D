#pragma once
#include <stdio.h>
#include "SDL3/SDL.h"

void FrameRate_init();

void FrameRate_updateCount();
double FrameRate_calculateAverageFPS();
void FrameRate_printAverageFPS();

void FrameRate_cleanUp();
