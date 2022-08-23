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

	TPSX_Context *context = TPSX_CreateContext(surface->pixels, RESX, RESY, TPSX_BGRA);

	TPSX_PixelBGRA white = {255, 255, 255, 255};
	TPSX_PixelBGRA red = {0, 0, 255, 255};

	TPSX_PixelBGRA tex_pixel[2][2] =
	{
		white, red,
		red, white
	};

	TPSX_Texture *tex = TPSX_CreateTexture(
		(TPSX_Pixel32*)tex_pixel,
		2, 
		2, 
		TPSX_BGRA);

	TPSX_Vertex vert[6];
	vert[0].pos.x = 0.4f;
	vert[0].pos.y = 0.1f;
	vert[0].pos.z = 0.1f;
	vert[0].tex_coord.u = 0.0f;
	vert[0].tex_coord.v = 0.0f;

	vert[1].pos.x = 0.2f;
	vert[1].pos.y = 0.3f;
	vert[1].pos.z = 0.1f;
	vert[1].tex_coord.u = 0.0f;
	vert[1].tex_coord.v = 1.0f;

	vert[2].pos.x = 0.1f;
	vert[2].pos.y = 0.9f;
	vert[2].pos.z = 0.1f;
	vert[2].tex_coord.u = 1.0f;
	vert[2].tex_coord.v = 0.0f;

	vert[3].pos.x = 0.5f;
	vert[3].pos.y = 0.1f;
	vert[3].pos.z = 0.1f;
	vert[3].tex_coord.u = 1.0f;
	vert[3].tex_coord.v = 1.0f;

	vert[4].pos.x = 0.9f;
	vert[4].pos.y = 0.3f;
	vert[4].pos.z = 0.1f;
	vert[4].tex_coord.u = 0.0f;
	vert[4].tex_coord.v = 1.0f;

	vert[5].pos.x = 0.5f;
	vert[5].pos.y = 0.9f;
	vert[5].pos.z = 0.1f;
	vert[5].tex_coord.u = 1.0f;
	vert[5].tex_coord.v = 0.0f;

	T_mat4 mat =
	{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};
	TPSX_RenderMesh(context, vert, 6, &mat, 1, tex);

	//show the rendered result
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);

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