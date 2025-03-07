#pragma once

#define MAPWIDTH 24
#define MAPHEIGHT 24

#include <math.h>

#include "SDL3/SDL.h"

#include "BeefPlayer.h"

void Raycast_raycastMapFromPlayerView(SDL_Renderer* renderer, BeefPlayer player, int w, int h, float *dest);

void Raycast_translateLineHeight(float *renderData, int offset, float *dest);

void Raycast_translateLineColor(float *renderData, int offset, float *dest);
