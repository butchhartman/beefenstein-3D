#include "BeefPlayer.h"


void BeefPlayer_init(BeefPlayer* beefplayer,
					double posX, double posY,
					double dirX, double dirY,
					double planeX, double planeY,
					double moveSpeed, float lastMouseX) {
	beefplayer->posX = posX;
	beefplayer->posY = posY;
	
	beefplayer->dirX = dirX;
	beefplayer->dirY = dirY;

	beefplayer->planeX = planeX;
	beefplayer->planeY = planeY;

	beefplayer->moveSpeed = moveSpeed;

	beefplayer->lastMouseX = lastMouseX;

}

