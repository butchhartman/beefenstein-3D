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
#define SENSITIVITY 1.75


// This function runs once on startup
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	
	SDL_SetAppMetadata("SDLbase", "1.0", "com.SDLbase.butchhartman");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("SDLbase", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_GRABBED, &window, &renderer)) {
		SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_HideCursor();
	FrameRate_init();
	BeefPlayer_init(&player, 22.0, 12.0, -1.0, 0.0, 0.0, 0.66, 4.5, 0.0f);
	SDL_WarpMouseInWindow(window, 640 / 2, 480 / 2);
	SDL_GetMouseState(&player.lastMouseX, NULL);
	
	drawData = (float*)malloc(DEFAULT_WIDTH * sizeof(float) * 5);

	return SDL_APP_CONTINUE; // The init function ran successfully
}

SDL_AppResult SDL_queryInputState(double deltatime) {
	SDL_PumpEvents();
	const unsigned char *keys = SDL_GetKeyboardState(NULL);;

	/*
	How I fixed my issues relating to the movement sytem:
	Before I was just moving along the player's facing direction for W and moving along its negative version for S.
	Then, for A and D, I would rotate the player's facing direction by 45 degrees and use that if a strafe and forward/back key was pressed simultaneously.
	Otherwise, for only a strafe input, I would rotate the front direction by 90 degrees and use that.

	This was inefficient and had a major problem in that you could not walk backwards and strafe in the correct direction.

	These problems were solved by creating a movement direction variable and adding the previously described vectors to it when their respective movement key is being pressed.
	The only problem with this approach was moving too fast on diagnols, which was fixed by simply normalizing the vector before applying the movement step.
	*/

	double moveDirX = 0;
	double moveDirY = 0;

	if (keys[SDL_SCANCODE_W] == 1) {
		moveDirX += player.dirX;
		moveDirY += player.dirY;
	}
	if (keys[SDL_SCANCODE_S] == 1) {
		moveDirX += -player.dirX;
		moveDirY += -player.dirY;
	}

	if (keys[SDL_SCANCODE_D]) {
		moveDirX += player.dirX * cos(-M_PI_2) - player.dirY * sin(-M_PI_2);
		moveDirY += player.dirY * cos(-M_PI_2) + player.dirX * sin(-M_PI_2);
	}

	if (keys[SDL_SCANCODE_A]) {
		moveDirX += player.dirX * cos(M_PI_2) - player.dirY * sin(M_PI_2);
		moveDirY += player.dirY * cos(M_PI_2) + player.dirX * sin(M_PI_2);
	}
	//printf("%.20f, %.20f\n", moveDirX, moveDirY);
	// vector normalization
	double vecLength = sqrt(pow(moveDirX, 2) + pow(moveDirY, 2));
	//printf("ORIGINAL VEC LENGTH: %f\n", vecLength);
	
	// avoid dividing 0/0
	// Comparing the moveDir <= 0.001 because direction rotations cause the movement vectors to not quite be 0, resulting in undefined behavior when all movement keys are held down. 
	// fabs is necessary, otherwise negative movement vectors will be clipped
	moveDirX = (fabs(moveDirX) <= 0.001 ) ? 0 : moveDirX/vecLength;
	moveDirY = (fabs(moveDirY) <= 0.001) ? 0 : moveDirY/vecLength;

	//vecLength = sqrt(pow(moveDirX, 2) + pow(moveDirY, 2));
	//printf("NORMAL VEC LENGTH: %f\n", vecLength);

	if (worldMap[(int)(player.posX + moveDirX * player.moveSpeed * deltatime)][(int)player.posY] == 0) {
		player.posX += moveDirX * player.moveSpeed * deltatime;
	}
	if (worldMap[(int)player.posX][(int)(player.posY + moveDirY * player.moveSpeed * deltatime)] == 0) {
		player.posY += moveDirY * player.moveSpeed * deltatime;
	}




	// Gets the mouse's current position in the window
	float currentMouseX;
	SDL_GetMouseState(&currentMouseX, NULL);

	// Calculate the distance the mouse has moved (scaled with deltatime & sens)
	double diff = (currentMouseX - player.lastMouseX) * deltatime * SENSITIVITY;

	// Rotate the camera plane and view direction
	double oldDirX = player.dirX;
	player.dirX = player.dirX * cos(-diff) - player.dirY * sin(-diff);
	player.dirY = oldDirX * sin(-diff) + player.dirY * cos(-diff);
	double oldPlaneX = player.planeX;
	player.planeX = player.planeX * cos(-diff) - player.planeY * sin(-diff);
	player.planeY = oldPlaneX * sin(-diff) + player.planeY * cos(-diff);

	// TODO : make work for any size screen

	// Reset player's mouse to middle of window
	SDL_WarpMouseInWindow(window, 640 / 2, 480 / 2);
	// Get the mouse state and set the player's mouse position back to middle of screen
	SDL_GetMouseState(&currentMouseX, NULL);
	player.lastMouseX = currentMouseX;

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