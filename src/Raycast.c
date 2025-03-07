#include "Raycast.h"
// TODO : document
extern Uint32 texture[8][64 * 64];
extern Uint32 buffer[480][640];

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

		int texNum = worldMap[mapX][mapY] - 1;

		double wallX;
		if (side == 0) {
			wallX = player.posY + perpWallDist * rayDirY;
		}
		else {
			wallX = player.posX + perpWallDist * rayDirX;
		}
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)(64)); // TODO : REPLACE 64 WITH TEXTURE WIDTH VARIABLE

		if (side == 0 && rayDirX > 0) {
			texX = 64 - texX - 1;  // TODO : REPLACE 64 WITH TEXTURE WIDTH VARIABLE
		}
		if (side == 1 && rayDirY < 0) {
			texX = 64 - texX - 1;  // TODO : REPLACE 64 WITH TEXTURE WIDTH VARIABLE
		}

		double step = 1.0 * 64 / lineHeight;

		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++) {
			int texY = (int)texPos & (64 - 1);  // TODO : REPLACE 64 WITH TEXTURE WIDTH VARIABLE
			texPos += step;
			Uint32 color = texture[texNum][64 * texY + texX];  // TODO : REPLACE 64 WITH TEXTURE WIDTH VARIABLE

			if (side == 1) {
				color = (color >> 1) & 8355711;
			}
			buffer[y][x] = color;
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
