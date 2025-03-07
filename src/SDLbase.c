// Code provided by :
// https://github.com/libsdl-org/SDL/blob/main/examples/renderer/01-clear/clear.c
// https://lodev.org/cgtutor/raycasting.html#The_Basic_Idea_
#include "SDLbase.h"

int windowWidth = DEFAULT_WIDTH;
int windowHeight = DEFAULT_HEIGHT;

// renderer is used to draw into the window every frame.
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

BeefPlayer player;

float *drawData;


#define MAPWIDTH 24
#define MAPHEIGHT 24


// This function runs once on startup
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	
	SDL_SetAppMetadata("SDLbase", "1.0", "com.SDLbase.butchhartman");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("SDLbase", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | , &window, &renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	FrameRate_init();
	BeefPlayer_init(&player, 22.0, 12.0, -1.0, 0.0, 0.0, 0.66, 10.0);

	drawData = (float*)malloc(DEFAULT_WIDTH * sizeof(float) * 5);

	return SDL_APP_CONTINUE; // The init function ran successfully
}

SDL_AppResult SDL_queryInputState(double deltatime) {
	SDL_PumpEvents();
	const unsigned char *keys = SDL_GetKeyboardState(NULL);;
	if (keys[SDL_SCANCODE_W] == 1) {
		if (worldMap[(int)(player.posX + player.dirX * player.moveSpeed * deltatime)][(int)player.posY] == 0) {
			player.posX += player.dirX * player.moveSpeed * deltatime;
		}
		if (worldMap[(int)player.posX][(int)(player.posY + player.dirY * player.moveSpeed)] == 0) {
			player.posY += player.dirY * player.moveSpeed * deltatime;
			printf("%f", deltatime);
		}
	}

	if (keys[SDL_SCANCODE_S] == 1) {
		if (worldMap[(int)(player.posX - player.dirX * player.moveSpeed * deltatime)][(int)player.posY] == 0) {
			player.posX -= player.dirX * player.moveSpeed * deltatime;
		}
		if (worldMap[(int)player.posX][(int)(player.posY - player.dirY * player.moveSpeed * deltatime)] == 0) {
			player.posY -= player.dirY * player.moveSpeed * deltatime;
		}
	}

	return SDL_APP_CONTINUE;
}

// This function runs when a new event (mouse input, keypress, etc) occurs.
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {

	switch (event->type) {
		case SDL_EVENT_KEY_DOWN:
			switch (event->key.key)
			{
				case SDLK_F: 
				{
					FrameRate_printAverageFPS();
					break;
				}

				case SDLK_ESCAPE: {
					return SDL_APP_SUCCESS;
					break;
				}
				default:

				break;
			}

		default:
			break;
	}

	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS; // Ends the program, reports a success to the OS. "Program ran successfully"
	}

	return SDL_APP_CONTINUE; // Carry on with the program
}

// This function runs once per frame. It is the beating heart behind the program
SDL_AppResult SDL_AppIterate(void* appstate) {
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	const double now = ((double)SDL_GetTicks()) / 1000.0f; // converts from ms to s
	

	// Clears the window with the draw color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);

	Raycast_raycastMapFromPlayerView(renderer, player, windowWidth, windowHeight, drawData);

	for (int i = 0; i < windowWidth; i++) {

		float lineVerts[2];
		Raycast_translateLineHeight(drawData, i, lineVerts);

		float lineColors[3];
		Raycast_translateLineColor(drawData, i, lineColors);

		SDL_SetRenderDrawColorFloat(renderer, lineColors[0], lineColors[1], lineColors[2], 1);
		SDL_RenderLine(renderer, (float)i, lineVerts[0], (float)i, lineVerts[1]);
	}
	
	// Put the newly-cleared rendering to the screen.
	SDL_queryInputState(FrameRate_getDeltaTime());
	SDL_RenderPresent(renderer);
	FrameRate_updateCount();

	return SDL_APP_CONTINUE; // Carry on with the program
}

// This function runs once when the program is closed.
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	// SDL cleans up the window/renderer for us
	FrameRate_cleanUp();
	free(drawData);
}