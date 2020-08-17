
int (*comparators[MAX_SORT_MODES]) (void *, void *) =
{
	ADT_Track_compare_by_name,
	ADT_Track_compare_by_artist,
	ADT_Track_compare_by_year,
	ADT_Track_compare_by_genre
};

typedef enum = 
{
	SORT_BY_NAME   = 0,
	SORT_BY_ARTIST = 1,
	SORT_BY_YEAR   = 2,
	SORT_BY_GENRE  = 3 

} sortmode_t;

status_t (*export_fx[MAX_EXPORT_FX]) (ADT_Vector_t *, FILE *) =
{
	ADT_Vector_export_as_csv,
	ADT_Vector_export_as_xml
};

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

typedef struct 
{
	format_t    format;
	sort_mode_t smode;
	char *		header;
	char *		footer;
	void *		context;

} setting_t;
