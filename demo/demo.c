#include <tpsx.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>

#define RESX 640
#define RESY 480

int main()
{
	if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
		printf("[ERROR] couldn't initialize SDL2");
	}
	SDL_Window *window = SDL_CreateWindow(
		"TPSX demo",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		RESX,
		RESY,
		0);

	SDL_Surface *surface = SDL_GetWindowSurface(window);

	TPSX_Context *context = TPSX_CreateContext(surface, RESX, RESY);

	//show the rendered result
	SDL_UpdateWindowSurface(window);

	//saving the screenshot
	char filename[100];
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	sprintf(filename, "%li.bmp", ts.tv_sec);
	SDL_SaveBMP(surface, filename);

	TPSX_DestroyContext(&context);
	if(context)
	{
		printf("[ERROR] context wasn't destroyed\n");
	}

	//quit
	SDL_Quit();
	return 0;
}