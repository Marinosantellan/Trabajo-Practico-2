#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MP3_HEADER_SIZE 		128
#define NUL 				    '\0'

#define PREFIJO_START_TAG 		0
#define PREFIJO_SPAN_TAG 		3	

#define PREFIJO_START_TITLE   	3
#define PREFIJO_SPAN_TITLE   	30

#define PREFIJO_START_ARTIST  	33
#define PREFIJO_SPAN_ARTIST  	30

#define PREFIJO_START_ALBUM   	63
#define PREFIJO_SPAN_ALBUM   	30

#define PREFIJO_START_YEAR     	93
#define PREFIJO_SPAN_YEAR     	4

#define PREFIJO_START_COMMENT  	97
#define PREFIJO_SPAN_COMMENT  	30

#define PREFIJO_START_GENRE     127
#define PREFIJO_SPAN_GENRE     	1

#define CHAR_GAP				32

typedef struct 
{
	char tag[PREFIJO_SPAN_TAG+1];
	char title[PREFIJO_SPAN_TITLE+1];
	char artist[PREFIJO_SPAN_ARTIST+1];
	char album[PREFIJO_SPAN_ALBUM+1];
	char year[PREFIJO_SPAN_YEAR+1];
	char comment[PREFIJO_SPAN_COMMENT+1];
	char genre;

}ADT_Track_t;

typedef enum
{
	OK,
	ERROR_NULL_POINTER,
	ERROR_NO_MEMORY

}status_t;


/****************************PROTOTYPES****************************/



int str_compare(const char *str_1, const char *str_2);



/****************************PROTOTYPES****************************/

status_t ADT_Track_create(ADT_Track_t **track)
{
	if(track == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if((*track = (ADT_Track_t *) calloc(1 , sizeof(ADT_Track_t))) == NULL)
	{
		return ERROR_NO_MEMORY;
	}
	return OK;
}

status_t ADT_Track_destroy(ADT_Track_t **track)
{
	if(track == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	free(*track);
	*track = NULL;

	return OK;
}

/*Primitiva que recibe dos ADT_Track_t e implementando lógicas de ordenamiento lexicográfico, devuelve*/
/* distintos valores si la cadena del cprimer argumento es de mayor, menor, o igual que la otra. Los valores*/
/*serán 1, -1 y 0 respectivamente. */

int ADT_Track_compare_by_title(const ADT_Track_t *track_1, const ADT_Track_t *track_2)   
{
	if( track_1 == NULL || track_2 == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	return str_compare(track_1->title, track_2->title); 
}

status_t ADT_Track_load(ADT_Track_t *track, FILE* fi)
{
	size_t len;
	char header[MP3_HEADER_SIZE];

	if(track == NULL || fi == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	fseek(fi, 0, SEEK_END);		/*si falla, fseek devuelve != 0, no se que nombre de error poner. De hecho, creo que no se validan*/		
    len = ftell(fi);							
    fseek(fi,len-MP3_HEADER_SIZE,SEEK_SET);

    fread(header,sizeof(char),MP3_HEADER_SIZE,fi);

    memcpy(track->tag,header+PREFIJO_START_TAG,PREFIJO_SPAN_TAG);
   	track->tag[PREFIJO_SPAN_TAG+1] = NUL;

    memcpy(track->title,header+PREFIJO_START_TITLE,PREFIJO_SPAN_TITLE);
    track->title[PREFIJO_SPAN_TITLE+1] = NUL;

    memcpy(track->artist,header+PREFIJO_START_ARTIST,PREFIJO_SPAN_ARTIST);
    track->artist[PREFIJO_SPAN_ARTIST+1] = NUL;

    memcpy(track->album,header+PREFIJO_START_ALBUM,PREFIJO_SPAN_ALBUM);
    track->album[PREFIJO_SPAN_ALBUM+1] = NUL;

    memcpy(track->year,header+PREFIJO_START_YEAR,PREFIJO_SPAN_YEAR);
    track->year[PREFIJO_SPAN_YEAR+1] = NUL;

    memcpy(track->comment,header+PREFIJO_START_COMMENT,PREFIJO_SPAN_COMMENT);
    track->comment[PREFIJO_SPAN_COMMENT+1] = NUL;

    memcpy(&(track->genre),header+PREFIJO_START_GENRE,PREFIJO_SPAN_GENRE);

    return OK;
}

/*
size_t ADT_Track_compare_by_artist(const ADT_Track_t **track_1, const ADT_Track_t**track_2); son iguales a las del título
size_t ADT_Track_compare_by_album(const ADT_Track_t **track_1, const ADT_Track_t**track_2); son iguales a las del título
size_t ADT_Track_compare_by_year(const ADT_Track_t **track_1, const ADT_Track_t**track_2);	se puede optimizar, porque sólo recibe números. Pero misma lógica

staus_t ADT_Track_export_as_CSV(ADT_Track **);
staus_t	ADT_Track_export_as_XML(ADT_Track **);
*/

int str_compare(const char *str_1, const char *str_2)
{
	char char_1, char_2;
	size_t i;

	for(i = 0; str_1[i] && str_2[i]; i++ )			
	{	
		if( str_1[i] != str_2[i] )
		{	
			char_1 = str_1[i];
			char_2 = str_2[i];

			if(isalnum(char_1))	 								
			{
				if(isalnum(char_2))
				{
					if(isupper(char_1))
					{
						char_1 += CHAR_GAP;
					}
					if(isupper(char_2))
					{
						char_2 += CHAR_GAP;
					}
					return (char_1 > char_2 ? 1 : -1);
				}
				return -1;
			}

			if(isalnum(char_2))
			{
				return 1;
			}
			return ( char_1 > char_2 ? 1 : -1);
		}
	}
	return 0;
}
