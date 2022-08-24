#include "tpsx.h"

TPSX_Texture* TPSX_CreateTexture(
    TPSX_Pixel32 *surface,
    u8 width,
    u8 height,
    enum TPSX_PixelType type)
{
	if(!surface)
	{
		return NULL;
	}
	if(!width)
	{
		return NULL;
	}
	if(!height)
	{
		return NULL;
	}

	TPSX_Texture *new_texture = malloc(sizeof(TPSX_Texture));
	if(!new_texture)
	{
		return NULL;
	}

	new_texture->pixels = surface;
	new_texture->width = width;
	new_texture->height = height;
	new_texture->type = type;
	return new_texture;
}

void TPSX_DestroyTexture(TPSX_Texture **texture)
{
	//safeguard if the context has already been deleted 
	if(*texture == NULL)
	{
		return;
	}

	free(*texture);
	*texture = NULL;
}


TPSX_PixelRGBA TPSX_SampleFromTextureRGBA(TPSX_Texture *texture, T_vec2 pos)
{
	TPSX_PixelRGBA pixel = { 255, 0, 255, 255};
	if(!texture)
	{
		return pixel;
	}

	//repeat the texture if the values are above 1.0f
	T_vec2 pos_repeated;
	pos_repeated.x = pos.x - (f32)(u32)pos.x;
	pos_repeated.y = pos.y - (f32)(u32)pos.y;
	u32 tex_pos_x = (f32)texture->width * pos_repeated.x;
	u32 tex_pos_y = (f32)texture->height * pos_repeated.y;
	if(texture->type == TPSX_RGBA)
	{
		TPSX_PixelRGBA *texel = (TPSX_PixelRGBA*)texture->pixels;
		texel += tex_pos_y * texture->width + tex_pos_x;
		pixel = *texel;
	}
	else
	{
		//converting to appropriate pixel format
		TPSX_PixelBGRA *texel = (TPSX_PixelBGRA*)texture->pixels;
		texel += tex_pos_y * texture->width + tex_pos_x;
		pixel.r = texel->r;
		pixel.g = texel->g;
		pixel.b = texel->b;
		pixel.a = texel->a;
	}
	return pixel;
}


TPSX_PixelBGRA TPSX_SampleFromTextureBGRA(TPSX_Texture *texture, T_vec2 pos)
{
	TPSX_PixelBGRA pixel = { 255, 0, 255, 255};
	if(!texture)
	{
		return pixel;
	}

	//repeat the texture if the values are above 1.0f
	T_vec2 pos_repeated;
	pos_repeated.x = pos.x - (f32)(u32)pos.x;
	pos_repeated.y = pos.y - (f32)(u32)pos.y;
	u32 tex_pos_x = (f32)texture->width * pos_repeated.x;
	u32 tex_pos_y = (f32)texture->height * pos_repeated.y;
	if(texture->type == TPSX_BGRA)
	{
		TPSX_PixelBGRA *texel = (TPSX_PixelBGRA*)texture->pixels;
		texel += tex_pos_y * texture->width + tex_pos_x;
		pixel = *texel;
	}
	else
	{
		//converting to appropriate pixel format
		TPSX_PixelRGBA *texel = (TPSX_PixelRGBA*)texture->pixels;
		texel += tex_pos_y * texture->width + tex_pos_x;
		pixel.r = texel->r;
		pixel.g = texel->g;
		pixel.b = texel->b;
		pixel.a = texel->a;
	}
	return pixel;
}
