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

	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);

	SDL_Window *window = SDL_CreateWindow(
		"TPSX demo",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		RESX,
		RESY,
		0);

	SDL_Surface *surface = SDL_GetWindowSurface(window);

	TPSX_Context *context = TPSX_CreateContext(surface->pixels, RESX, RESY, TPSX_BGRA);

	TPSX_PixelBGRA white = {255, 255, 255, 240};
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

	const u32 num_verts = 9;
	TPSX_Vertex vert[num_verts];

	vert[0].pos.x = 0.9f;
	vert[0].pos.y = 0.1f;
	vert[0].pos.z = 0.5f;
	vert[0].tex_coord.u = 0.0f;
	vert[0].tex_coord.v = 0.0f;

	vert[1].pos.x = 0.2f;
	vert[1].pos.y = 0.3f;
	vert[1].pos.z = 0.5f;
	vert[1].tex_coord.u = 0.0f;
	vert[1].tex_coord.v = 35.0f;

	vert[2].pos.x = 0.1f;
	vert[2].pos.y = 0.9f;
	vert[2].pos.z = -1.5f;
	vert[2].tex_coord.u = 3.0f;
	vert[2].tex_coord.v = 0.0f;

	vert[3].pos.x = 0.5f;
	vert[3].pos.y = 0.1f;
	vert[3].pos.z = 0.1f;
	vert[3].tex_coord.u = 5.0f;
	vert[3].tex_coord.v = 5.0f;

	vert[4].pos.x = 0.9f;
	vert[4].pos.y = 0.3f;
	vert[4].pos.z = 0.1f;
	vert[4].tex_coord.u = 0.0f;
	vert[4].tex_coord.v = 5.0f;

	vert[5].pos.x = 0.5f;
	vert[5].pos.y = 0.9f;
	vert[5].pos.z = 1.1f;
	vert[5].tex_coord.u = 5.0f;
	vert[5].tex_coord.v = 0.0f;

	vert[6].pos.x = 1.0f;
	vert[6].pos.y = 0.0f;
	vert[6].pos.z = 1.0f;
	vert[6].tex_coord.u = 3.0f;
	vert[6].tex_coord.v = 3.0f;

	vert[7].pos.x = 1.2f;
	vert[7].pos.y = 1.0f;
	vert[7].pos.z = 1.0f;
	vert[7].tex_coord.u = 0.0f;
	vert[7].tex_coord.v = 3.0f;

	vert[8].pos.x = 0.0f;
	vert[8].pos.y = 0.3f;
	vert[8].pos.z = 1.0f;
	vert[8].tex_coord.u = 3.0f;
	vert[8].tex_coord.v = 0.0f;


	T_mat4 translate =
	{
		1.0f, 0.0f, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,			
	};

	T_mat4 back_translate =
	{
		1.0f, 0.0f, 0.0f, -0.5f,
		0.0f, 1.0f, 0.0f, -0.5f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,			
	};

	TPSX_Vertex vert_translated[num_verts];
	TPSX_Vertex vert_rotated[num_verts];
	TPSX_Vertex vert_transformed[num_verts];

	f32 angle = 0.0f;
	u32 frames = 0;
	float ms_before = SDL_GetTicks();
	while(frames < 1000)
	{
		frames++;
		TPSX_ClearRenderTarget(context);
		angle+= 0.01f;
		T_mat4 rot =
		{
			cos(angle), -sin(angle), 0.0f, 0.0f,
			sin(angle), cos(angle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		TPSX_TransformVertices(vert, vert_translated, num_verts, back_translate);
		TPSX_TransformVertices(vert_translated, vert_rotated, num_verts, rot);
		TPSX_TransformVertices(vert_rotated, vert_transformed, num_verts, translate);
		TPSX_SortTriangles(vert, num_verts);
		TPSX_RenderMesh(context, vert_transformed, num_verts, tex);

		//show the rendered result
		SDL_UpdateWindowSurface(window);
	}
	float ms_after = SDL_GetTicks();
	float ms = ms_after - ms_before;
	printf("FRAMES: %i\n", frames);

	printf("ms per frame on avg: %f ms\n", ms/frames);
	printf("total render time: %f ms\n", ms);

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

	//reset to the original desktop resolution
	SDL_SetWindowSize(
		window,
		dm.w,
		dm.h);

	//quit
	SDL_Quit();
	return 0;
}
