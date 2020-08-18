#include <string.h>
#include "errors.h"
#include "vector.h"
#include "track.h"
#include "types.h"
#include "settings.h"

int (*comparators[MAX_SORT_MODES]) (const void *, const void *) =
{
	compare_by_title,
	compare_by_artist,
	compare_by_year,
	compare_by_genre
};

void (*printers[MAX_FMT_MODES]) (const void *, void *, FILE *) = 
{
	print_as_csv,
	print_as_xml
};

status_t process_config(setting_t *settings, char *fmt_reference, char *sort_reference)
{
	status_t st;

	if(settings == NULL || fmt_reference == NULL || sort_reference == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if((st = set_fmt(settings, fmt_reference)) != OK)
	{
		return st;
	}

	if((st = set_sortmode(settings, sort_reference)) != OK)
	{
		return st;
	}

	if(settings->format == FMT_CSV)
	{
		if ((st = set_csv_context(settings)) != OK)
		{
			return st;
		}
	}
	else 
		if((st = set_xml_context(settings)) != OK)
		{
			return st;
		}

	return OK;
}

status_t set_Vector_config(ADT_Vector_t *vector, setting_t *settings)
{
	status_t st;

	if(settings == NULL || vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if((st = ADT_Vector_set_printer(vector, printers[settings->format])) != OK)
	{
		return st;
	}

	if((st = ADT_Vector_set_comparator(vector, comparators[settings->smode])) != OK)
	{
		return st;
	}

	if((st = ADT_Vector_set_destructor(vector, destructor)) != OK)
	{
		return st;
	}
	
	if((st = ADT_Vector_set_header(vector, settings->context.header)) != OK)
	{
		return st;
	}

	if((st = ADT_Vector_set_footer(vector, settings->context.footer)) != OK)
	{
		return st;
	}

	if((st = ADT_Vector_set_context(vector, settings->context.context)) != OK)
	{
		return st;
	}

	return OK;
}

/*sub-modulos de settings.c*/

status_t set_fmt(setting_t *settings, char *fmt_reference)
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
	}
	if(c == MAX_FMT_MODES)
	{
		return ERROR_INVALID_INVOCATION_FMT;
	}
	return OK;
}

status_t set_sortmode(setting_t *settings, char *sort_reference)
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
	}
	if(c == MAX_SORT_MODES)
	{
		return ERROR_INVALID_INVOCATION_SORT_MODE;	
	}
	return OK;
}

status_t set_csv_context(setting_t *settings)
{
	/*settins csv*/
	static char   *csv_header    = CSV_FMT_HEADER;
	static char   *csv_footer    = CSV_FMT_FOOTER; 
	static char    csv_delimiter = PIPE;

	if(settings == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	settings->context.header  =  csv_header;
	settings->context.footer  =  csv_footer;
	settings->context.context = &csv_delimiter;

	return OK;
}

status_t set_xml_context(setting_t *settings)
{
	/*settings xml*/
	static char   *xml_header    = XML_FMT_HEADER;
	static char   *xml_footer    = XML_FMT_FOOTER;
	static size_t  xml_init_tabs = XML_FMT_INIT_TABS;

	if(settings == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	settings->context.header  =  xml_header;
	settings->context.footer  =  xml_footer;
	settings->context.context = &xml_init_tabs;

	return OK;
}

/**********************************************auxiliar functions**********************************************/
void destructor(const void *track)
{
	ADT_Track_destroy((ADT_Track_t *)track);	
} 

int compare_by_title(const void *track_1, const void *track_2)
{	
	return ADT_Track_compare_by_title((const ADT_Track_t *)track_1,(const ADT_Track_t *)track_2);
}
int compare_by_artist(const void *track_1, const void *track_2)
{	
	return ADT_Track_compare_by_artist((const ADT_Track_t *)track_1,(const ADT_Track_t *)track_2);
}
int compare_by_year(const void *track_1, const void *track_2)
{	
	return ADT_Track_compare_by_year((const ADT_Track_t *)track_1,(const ADT_Track_t *)track_2);
}
int compare_by_genre(const void *track_1, const void *track_2)
{	
	return ADT_Track_compare_by_genre((const ADT_Track_t *)track_1,(const ADT_Track_t *)track_2);
}

void print_as_csv(const void *track, void *del, FILE *fo)
{
	ADT_Track_print_as_csv((const ADT_Track_t *)track, (const char *) del, fo);
}
void print_as_xml(const void *track, void *init_tabs, FILE *fo)
{
	ADT_Track_print_as_xml((const ADT_Track_t *)track, (const size_t *) init_tabs, fo);
}
/**********************************************auxiliar functions**********************************************/
