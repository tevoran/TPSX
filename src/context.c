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
	context->surface_type = type;
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
