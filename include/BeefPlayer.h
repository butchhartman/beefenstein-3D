#pragma once


typedef struct {
	double posX;
	double posY;

	double dirX;
	double dirY;

	double planeX;
	double planeY;

	double moveSpeed;

	float lastMouseX;
} BeefPlayer;

void BeefPlayer_init(BeefPlayer *beefplayer, 
					double posX, double posY, 
					double dirX, double dirY,
					double planeX, double planeY,
					double moveSpeed, float lastMouseX);