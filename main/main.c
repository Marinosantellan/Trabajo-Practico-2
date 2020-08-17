#include <stdio.h>


void (*printers[MAX_PRINTERS]) (const void * , void *, FILE *) = 
{
	ADT_Track_print_as_csv,
	ADT_Track_print_as_xml
};


typedef enum = 
{
	FMT_CSV,
	FMT_XML

}	format_t;

typedef enum = 
{
	SORT_BY_ARTIST,
	SORT_BY_GENRE,
	SORT_BY_NAME,
	SORT_BY_YEAR

} smode_t;



int main(int argc, char *argv[])
{
	status_t st;
	comparator_t fcomparator;
	printer_t 	 fprinter;
	destructor_t fdestructor;
	format_t	 format;
	ADT_Vector_t *vector;
	FILE *fo; 

	if((st = validate_cla( argc, argv)) != OK)
	{
		show_error(st);
		return st;	
	}

	if((fo = fopen(argv[CMD_ARG_NAME_OUTPUT_FILE], "wt")) == NULL)
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

	if((st = process_input(argv, &fcomparator, &fprinter, &format)) != OK)
	{
		show_error(st);
		return st;
	}

	if((st = set_vector_config(vector, fprinter , fcomparator, fdestructor)) != OK)
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
