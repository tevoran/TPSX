#include "tpsx.h"

TPSX_Context* TPSX_CreateContext(void *render_target, u16 resx, u16 resy, enum TPSX_PixelType type)
{
	TPSX_Context *context = malloc(sizeof(TPSX_Context));
	if(!context)
	{
		return NULL;
	}

	context->is_valid = TPSX_VALID;
	context->target_surface = render_target;
	if(!render_target)
	{
		context->is_valid = TPSX_NOT_VALID;
	}
	context->resx = resx;
	context->resy = resy;
	context->type = type;
	return context;
}

void TPSX_DestroyContext(TPSX_Context **context)
{
	//safeguard if the context has already been deleted 
	if(*context == NULL)
	{
		return;
	}

	free(*context);
	*context = NULL;
}

void TPSX_ClearRenderTarget(TPSX_Context *context)
{
	TPSX_PixelBGRA pixel_bgra = {0,0,0,255};
	TPSX_PixelRGBA pixel_rgba = {0,0,0,255};
	TPSX_PixelBGRA *ptr_bgra = (TPSX_PixelBGRA*)context->target_surface;
	TPSX_PixelRGBA *ptr_rgba = (TPSX_PixelRGBA*)context->target_surface;
	if(context->type == TPSX_BGRA)
	{
		for(u32 i = 0; i < context->resx * context->resy; i++)
		{
			*ptr_bgra = pixel_bgra;
			ptr_bgra++;
		}
	}
	else
	{
		for(u32 i = 0; i < context->resx * context->resy; i++)
		{
			*ptr_rgba = pixel_rgba;
			ptr_rgba++;
		}

	}
}
