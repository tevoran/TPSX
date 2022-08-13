#include <tpsx.h>
#include <SDL2/SDL.h>
#include <time.h>

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
		640,
		480,
		0);

	SDL_Surface *surface = SDL_GetWindowSurface(window);

	//show the rendered result
	SDL_UpdateWindowSurface(window);

	//saving the screenshot
	char filename[100];
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	sprintf(filename, "%li.bmp", ts.tv_sec);
	SDL_SaveBMP(surface, filename);

	//quit
	SDL_Quit();
	return 0;
}