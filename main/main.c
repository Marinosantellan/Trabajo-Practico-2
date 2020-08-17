#include <stdio.h>
#include "vector.h"
#include "track.h"

int main(int argc, char *argv[])
{
	status_t st;
	char *name_fo_reference;
	char *sort_reference;
	char *fmt_reference;
	setting_t settings;

	ADT_Vector_t *vector;
	FILE *fo; 
	

	if((st = validate_cla(argc, argv, &fmt_reference, &sort_reference, &name_fo)) != OK)
	{
		show_error(st);
		return st;	
	} 

	if((st = process_config(&settings, fmt_reference, sort_reference)) != OK)
	{
		show_error(st);
		return st;
	}






	if((fo = fopen(name_fo, "wt")) == NULL)
	{
		st = ERROR_OPENING_FILE;
		show_error(st);
		return st;
	}

	if((st = ADT_Vector_create(&vector)) != OK)
	{
		show_error(st);
		return st;
	}
	/*if((st = process_input(argv, &fcomparator, &fprinter, &format)) != OK)
	{
		show_error(st);
		return st;
	}*/
	if((st = set_Vector_config(vector, printers[format], comparators[smode], ADT_Track_destroy)) != OK)
	{
		show_error(st);
		return st;
	}

	if((st = process_mp3(argv, &vector, format, fo)) != OK)
	{
		show_error(st);
		return st;
	}

	if((st = ADT_Vector_destroy(&vector)) != OK)/*Teoricamente no falla nunca, solo por seguridad*/
	{
		show_error(st);
		return st;
	}

	if(fclose(fo) == EOF)
	{
		show_error(ERROR_NO_DISK_MEMORY);
		return ERROR_NO_DISK_MEMORY;
	}

	return EXIT_SUCCESS;
}

status_t process_cla(int argc, char *argv, char **fmt_reference, char **sort_reference, char **name_fo)
{
	size_t i;

	if(argv == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if(argc < MIN_ARGS)
	{
		return ERROR_INVALID_INVOCATION;
	}

	for(i = 1; i < MIN_ARGS; i += 2)
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
			*name_fo = argv[i+1];
		}
		else 
		{
			return ERROR_INVALID_INVOCATION;
		}	
	}
	return OK;
}


status_t set_Vector_config(ADT_Vector_t *vector, printer_t printer, comparator_t comparator, destructor_t destructor)
{
	if(vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if((st = ADT_Vector_set_printer(vector, printer)) != OK)
	{
		return st;
	}

	if((st = ADT_Vector_set_comparator(vector, comparator)) != OK)
	{
		return st;
	}

	if((st = ADT_Vector_set_destructor(vector, destructor)) != OK)
	{
		return st;
	}
	
	return OK;
}
