#include <string.h>
#include "types.h"

#define MAX_SORT_MODES 4




status_t process_config(setting_t *settings, char *fmt_reference, char *sort_reference)
{
	if(settings == NULL || fmt_reference == NULL || sort_reference == NULL)
	{
		return ERROR_NULL_POINTER;
	}


	if((st = get_fmt(settings, fmt_reference)) != OK)
	{
		return st;
	}

	if((st = get_sortmode(settings, sort_reference)) != OK)
	{
		return st;
	}

	return OK;
}

status_t get_fmt(setting_t *settings, char *fmt_reference)
{
	size_t c;

	char *fmt_modes[MAX_FMT_MODES] =
	{
		"csv",
		"xml"
	};

	if(settings == NULL || fmt_reference == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	for(c = 0; c < MAX_FMT_MODES; c++)
	{
		if(!strcmp(fmt_reference,fmt_modes[c]))
		{
			settings->format = c;
			break;
		}
		if(c == MAX_FMT_MODES)
		{
			return ERROR_INVALID_FMT_INVOCATION;
		}
	}
	return OK;
}

status_t get_sortmode(setting_t *settings, char *sort_reference)
{
	size_t c;

	char *sort_modes[MAX_SORT_MODES] =
	{
		"name",
		"artist",
		"year",
		"genre"			
	};

	for(c = 0; c < MAX_SORT_MODES; c++)
	{
		if(!strcmp(sort_reference, sort_modes[c]))
		{
			settings->smode = c;
			break;
		}
		if(c == MAX_SORT_MODES)
		{
			return ERROR_INVALID_SORT_MODE_INVOCATION;	
		}
	}
	return OK;
}