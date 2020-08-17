#ifndef TRACK_H
#define TRACK_H

#define MP3_HEADER_SIZE 		128
#define NUL						'\0'
#define HT 					    '\t'	

#define INDEX_START_TAG 		0
#define INDEX_SPAN_TAG 			3	

#define INDEX_START_TITLE   	3
#define INDEX_SPAN_TITLE   		30

#define INDEX_START_ARTIST  	33
#define INDEX_SPAN_ARTIST  		30

#define INDEX_START_ALBUM   	63
#define INDEX_SPAN_ALBUM   		30

#define INDEX_START_YEAR     	93
#define INDEX_SPAN_YEAR      	4

#define INDEX_START_COMMENT  	97
#define INDEX_SPAN_COMMENT   	30

#define INDEX_START_GENRE    	127
#define INDEX_SPAN_GENRE     	1

#define TRACK_FIRST_BRANCH_TAB 	'\t'


#define TAG_START_TRACK			"<track>"
#define TAG_END_TRACK 			"</track>"

#define TAG_START_TITLE			"<name>"
#define TAG_END_TITLE 			"</name>"

#define TAG_START_ARTIST 		"<artist>"
#define TAG_END_ARTIST 			"</artist>"

#define TAG_START_GENRE 		"<genre>"
#define TAG_END_GENRE 			"</genre>"

#define TAG_START_YEAR 			"<year>"
#define TAG_END_YEAR 			"</year>"

#define CHAR_GAP				32
#define AUX_SIZE 				15


/************************************TYPEDEF'S********************************/
typedef enum
{
	
	OK,
	ERROR_NULL_POINTER,
	ERROR_NO_MEMORY,
	ERROR_NO_COMPARATOR_SETTED,
	ERROR_NO_PRINTER_SETTED,
	ERROR_NO_CONTEXT_SETTED,
	ERROR_NO_HEADER_SETTED,
	ERROR_NO_FOOTER_SETTED

}status_t;

typedef struct 
{
	char     tag[INDEX_SPAN_TAG+1];
	char   title[INDEX_SPAN_TITLE+1];
	char  artist[INDEX_SPAN_ARTIST+1];
	char   album[INDEX_SPAN_ALBUM+1];
	char    year[INDEX_SPAN_YEAR+1];
	char comment[INDEX_SPAN_COMMENT+1];
	char genre;

}ADT_Track_t;	
/************************************TYPEDEF'S********************************/

/************************************PROTOTIPOS************************************/
status_t 	ADT_Track_create(ADT_Track_t **);
status_t 	ADT_Track_destroy(ADT_Track_t **);
status_t 	ADT_Track_load_from_mp3(ADT_Track_t *, FILE*);
int 		ADT_Track_compare_by_title(const ADT_Track_t *, const ADT_Track_t *);
int 		ADT_Track_compare_by_artist(const ADT_Track_t *, const ADT_Track_t *);
int 		ADT_Track_compare_by_album(const ADT_Track_t *, const ADT_Track_t *);
int 		ADT_Track_compare_by_year(const ADT_Track_t *, const ADT_Track_t *);
int 		strcmp_optimized(const char *, const char *);
status_t 	ADT_Track_print_as_csv(ADT_Track_t *, const char *, FILE * );
status_t 	ADT_Track_print_as_xml(ADT_Track_t *, const size_t * , FILE * );
/************************************PROTOTIPOS************************************/


#endif