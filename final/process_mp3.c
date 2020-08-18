#include <stdio.h>
#include "vector.h"
#include "track.h"
#include "process_mp3.h"

status_t load_mp3( char* argv[] , size_t mp3_amount, ADT_Vector_t *vector)
{
	ADT_Track_t *track;
	status_t st;
	size_t i;
	FILE *fi;

	if (argv == NULL || vector == NULL)
		return ERROR_NULL_POINTER;

	for(i = CMD_ARG_MP3_FILE_START; i < mp3_amount ; i++)
	{
		if((fi = fopen(argv[i], "rb")) == NULL)
		{
			return ERROR_OPENING_FILE;
		}

		if ((st = ADT_Track_create(&track)) != OK)
		{
			return st;
		}

		if((st = ADT_Track_load_from_mp3(track, fi)) != OK)
		{
			return st;
		}

		if ((st = ADT_Vector_append(vector, track)) != OK)
		{
			return st;
		}
	}

	return OK;
}

/*status_t vector_export(ADT_Vector_t *vector, format_t format, FILE *fo)
{
	status_t st;

	if(vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if(format == FMT_XML)
	{
		if((st = ADT_Vector_export_as_xml(vector,fo)) != OK)
		{
			return st;
		}
	}
	else
	{
		if((st = ADT_Vector_export_as_csv(vector,fo)) != OK)
		{
			return st;
		}
	}

	return OK;
}

status_t process_mp3( char* argv[], size_t mp3_amount, ADT_Vector_t **vector, format_t format, FILE* fo)  
{
	status_t st;

	if(argv == NULL || vector == NULL || fo == NULL)
	{
		ADT_Vector_destroy(vector);
		return ERROR_NULL_POINTER;
	}

	if((st = load_mp3(argv, mp3amount, *vector)) != OK)
	{
		ADT_Vector_destroy(vector); que pasaría si ya hubiese fallado por ADT_Vector_append? 
		return st;
	}

	if((st = ADT_Vector_sort(*vector)) != OK)
	{
		ADT_Vector_destroy(vector);
		return st;
	}

	if((st = vector_export(*vector, format, fo)) != OK)
	{
		ADT_Vector_destroy(vector);
		return st;
	}

	return OK;
}
*/