#ifndef TYPES_H 
#define TYPES_H

typedef enum 
{
	SORT_BY_NAME   = 0,
	SORT_BY_ARTIST = 1,
	SORT_BY_YEAR   = 2,
	SORT_BY_GENRE  = 3 

} sortmode_t;

typedef enum 
{
	FMT_CSV,
	FMT_XML

}	format_t;

typedef struct 
{		
	char *	header;
	char *	footer;
	void *  context;
	
} context_t;

typedef struct 
{
	format_t    format;
	sortmode_t  smode;
	context_t 	context;

} setting_t;


#endif