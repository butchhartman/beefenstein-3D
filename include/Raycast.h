#pragma once



#include <math.h>

#include "SDL3/SDL.h"

#include "BeefPlayer.h"

extern int worldMap[24][24];

void Raycast_raycastMapFromPlayerView(SDL_Renderer* renderer, BeefPlayer player, int w, int h, float *dest);

void Raycast_translateLineHeight(float *renderData, int offset, float *dest);

void Raycast_translateLineColor(float *renderData, int offset, float *dest);
