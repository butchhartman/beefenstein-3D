#include "Raycast.h"
// TODO : document


void Raycast_raycastMapFromPlayerView(SDL_Renderer *renderer ,BeefPlayer player, int w, int h, float *dest) {

	for (int x = 0; x < w; x++) {
		double cameraX = 2 * x / (double)w - 1;
		double rayDirX = player.dirX + player.planeX * cameraX;
		double rayDirY = player.dirY + player.planeY * cameraX;

		int mapX = (int)player.posX;
		int mapY = (int)player.posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0f / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0f / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side = 0;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (player.posX - mapX) * deltaDistX;
		} 
		else {
			stepX = 1;
			sideDistX = (mapX + 1.0f - player.posX) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (player.posY - mapY) * deltaDistY;
		}
		else {
			stepY = 1;
			sideDistY = (mapY + 1.0f - player.posY) * deltaDistY;
		}

		while (hit == 0) {

			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (worldMap[mapX][mapY] > 0) {
				hit = 1;
			}
		}

		if (side == 0) {
			perpWallDist = (sideDistX - deltaDistX);
		}
		else {
			perpWallDist = (sideDistY - deltaDistY);
		}

		float lineHeight = (float)(h / perpWallDist);

		float drawStart = (-lineHeight / 2.0f) + (h / 2.0f);

		if (drawStart < 0) {
			drawStart = 0;
		}

		float drawEnd = (lineHeight / 2.0f) + (h / 2.0f);

		if (drawEnd >= h) {
			drawEnd = (float)(h - 1);
		}

		float color[3] = { 0 };

		switch (worldMap[mapX][mapY]){

			case 1:
				color[0] = 1.0f;
				break;
			case 2:
				color[1] = 1.0f;
				break;
			case 3:
				color[2] = 1.0f;
				break;
			case 4:
				color[0] = 1.0f;
				color[1] = 1.0f;
				color[2] = 1.0f;
				break;
			default:
				color[0] = 1.0f;
				color[1] = 1.0f;
				color[2] = 1.0f;
				break;
		}

		if (side == 1) {
			color[0] /= 2.0f;
			color[1] /= 2.0f;
			color[2] /= 2.0f;
		}

		dest[x * 5] = drawStart;
		dest[x * 5 + 1] = drawEnd;
		dest[x * 5 + 2] = color[0];
		dest[x * 5 + 3] = color[1];
		dest[x * 5 + 4] = color[2];
	}
}

void Raycast_translateLineHeight(float *renderData, int offset, float *dest)
{
	//start
	dest[0] = renderData[offset * 5];
	//end
	dest[1] = renderData[offset * 5 + 1];
}

void Raycast_translateLineColor(float *renderData, int offset, float*dest)
{
	// c1
	dest[0] = renderData[offset * 5 + 2];
	//c2
	dest[1] = renderData[offset * 5 + 3];
	//c3
	dest[2] = renderData[offset * 5 + 4];
}
