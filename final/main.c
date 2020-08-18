#include <stdio.h>
#include <string.h>
#include "types.h"
#include "errors.h"
#include "vector.h"
#include "track.h"
#include "settings.h"
#include "main.h"

status_t (*export_fx[MAX_PRINTERS]) (const ADT_Vector_t *, FILE *) =
{
	ADT_Vector_export_as_csv,
	ADT_Vector_export_as_xml
};

int main(int argc, char *argv[])
{
	status_t st;
	char *name_fo_reference;
	char *sort_reference;
	char *fmt_reference;
	setting_t settings;

	ADT_Vector_t *vector;
	FILE *fo; 

	if((st = validate_cla(argv, argc, &fmt_reference, &sort_reference, &name_fo_reference)) != OK)
	{
		show_error(st);
		return st;	
	}

	if((fo = fopen(name_fo_reference, "wt")) == NULL)
	{
		st = ERROR_OPENING_FILE;
		show_error(st);
		return st;
	}

	if((st = process_config(&settings, fmt_reference, sort_reference)) != OK)
	{
		fclose(fo);
		show_error(st);
		return st;
	}

	if((st = ADT_Vector_create(&vector)) != OK)
	{
		fclose(fo);
		show_error(st);
		return st;
	}

	if((st = set_Vector_config(vector, &settings)) != OK)
	{
		fclose(fo);
		ADT_Vector_destroy(&vector);
		show_error(st);
		return st;
	}

	if((st = load_mp3(argv, argc, vector)) != OK)
	{
		fclose(fo);
		ADT_Vector_destroy(&vector);
		show_error(st);
		return st;
	}

	if((st = ADT_Vector_sort(vector)) != OK)/*Teoricamente no falla nunca, solo por seguridad*/
	{
		fclose(fo);
		ADT_Vector_destroy(&vector);
		show_error(st);
		return st;
	}

	if((st = (*export_fx[settings.format])(vector, fo)) != OK)
	{
		fclose(fo);
		ADT_Vector_destroy(&vector);
		show_error(st);
		return st;
	}

	if((st = ADT_Vector_destroy(&vector)) != OK)/*Teoricamente no falla nunca, solo por seguridad*/
	{
		fclose(fo);
		show_error(st);
		return st;
	}

	if(fclose(fo) == EOF)
	{
		show_error(ERROR_NO_DISK_MEMORY);
		return ERROR_NO_DISK_MEMORY;
	}

	return OK;
}

status_t validate_cla(char* argv[], int argc, char **fmt_reference, char **sort_reference, char **name_fo_reference)
{
	size_t i;

	if(argv == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if(argc < MIN_CMD_ARGS)
	{
		return ERROR_INVALID_INVOCATION;
	}

	for(i = 1; i < CMD_ARG_MP3_FILE_START ; i += 2)
	{
		if(!strcmp(argv[i],CMD_ARG_FMT_TOKEN))
		{
			*fmt_reference = argv[i+1];
		}
		else if(!strcmp(argv[i], CMD_ARG_SORT_TOKEN))
		{
			*sort_reference = argv[i+1];
		}
		else if(!strcmp(argv[i], CMD_ARG_OUTPUT_FILE_TOKEN))
		{
			*name_fo_reference = argv[i+1];
		}
		else 
		{
			return ERROR_INVALID_INVOCATION;
		}	
	}
	return OK;
}

status_t load_mp3(char* argv[] , int argc, ADT_Vector_t *vector)/*carga todos los indices de los mp3 en el vector*/
{
	ADT_Track_t *aux_track_ptr;
	status_t st;
	size_t i;
	FILE *mp3;
	/*size_t 	mp3_amount = argc - CMD_ARG_MP3_FILE_START;*/ 

	if(argv == NULL || vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	for(i = CMD_ARG_MP3_FILE_START; i < argc ; i++)
	{
		if((mp3 = fopen(argv[i], "rb")) == NULL)
		{
			return ERROR_OPENING_FILE;
		}

		if((st = ADT_Track_create(&aux_track_ptr)) != OK)
		{
			return st;
		}

		if((st = ADT_Track_load_from_mp3(aux_track_ptr, mp3)) != OK)
		{
			return st;
		}

		if((st = ADT_Vector_append(vector, aux_track_ptr)) != OK)
		{
			return st;
		}
	}
	return OK;
}
