#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "track.h"

char *genres[] =
{
"Blues",
"Classic Rock",
"Country",
"Dance",
"Disco",
"Funk",
"Grunge",
"Hip-Hop",
"Jazz",
"Metal",
"New Age",
"Oldies",
"Other",
"Pop",
"R&B",
"Rap",
"Reggae",
"Rock",
"Techno",
"Industrial",
"Alternative",
"Ska",
"Death Metal",
"Pranks",
"Soundtrack",
"Euro-Techno",
"Ambient",
"Trip-Hop",
"Vocal",
"Jazz+Funk",
"Fusion",
"Trance",
"Classical",
"Instrumental",
"Acid",
"House",
"Game",
"Sound Clip",
"Gospel",
"Noise",
"AlternRock",
"Bass",
"Soul",
"Punk",
"Space",
"Meditative",
"Instrumental Pop",
"Instrumental Rock",
"Ethnic",
"Gothic",
"Darkwave",
"Techno-Industrial",
"Electronic",
"Pop-Folk",
"Eurodance",
"Dream",
"Southern Rock",
"Comedy",
"Cult",
"Gangsta",
"Top 40",
"Christian Rap",
"Pop/Funk",
"Jungle",
"Native American",
"Cabaret",
"New Wave",
"Psychadelic",
"Rave",
"Showtunes",
"Trailer",
"Lo-Fi",
"Tribal",
"Acid Punk",
"Acid Jazz",
"Polka",
"Retro",
"Musical",
"Rock & Roll",
"Hard Rock",
"Folk",
"Folk-Rock",
"National Folk",
"Swing",
"Fast Fusion",
"Bebob",
"Latin",
"Revival",
"Celtic",
"Bluegrass",
"Avantgarde",
"Gothic Rock",
"Progressive Rock",
"Psychedelic Rock",
"Symphonic Rock",
"Slow Rock",
"Big Band",
"Chorus",
"Easy Listening",
"Acoustic",
"Humour",
"Speech",
"Chanson",
"Opera",
"Chamber Music",
"Sonata",
"Symphony",
"Booty Brass",
"Primus",
"Porn Groove",
"Satire",
"Slow Jam",
"Club",
"Tango",
"Samba",
"Folklore",
"Ballad",
"Poweer Ballad",
"Rhytmic Soul",
"Freestyle",
"Duet",
"Punk Rock",
"Drum Solo",
"A Capela",
"Euro-House",
"Dance Hall"
};

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

status_t ADT_Track_load(ADT_Track_t *track, FILE* fi)
{
	size_t len;
	char header[MP3_HEADER_SIZE];

	if(track == NULL || fi == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	fseek(fi, 0, SEEK_END);			
    len = ftell(fi);							
    fseek(fi,len-MP3_HEADER_SIZE,SEEK_SET);

    fread(header,sizeof(char),MP3_HEADER_SIZE,fi);

    memcpy(track->tag,header+INDEX_START_TAG,INDEX_SPAN_TAG);
   	track->tag[INDEX_SPAN_TAG+1] = NUL;

    memcpy(track->title,header+INDEX_START_TITLE,INDEX_SPAN_TITLE);
    track->title[INDEX_SPAN_TITLE+1] = NUL;

    memcpy(track->artist,header+INDEX_START_ARTIST,INDEX_SPAN_ARTIST);
    track->artist[INDEX_SPAN_ARTIST+1] = NUL;

    memcpy(track->album,header+INDEX_START_ALBUM,INDEX_SPAN_ALBUM);
    track->album[INDEX_SPAN_ALBUM+1] = NUL;

    memcpy(track->year,header+INDEX_START_YEAR,INDEX_SPAN_YEAR);
    track->year[INDEX_SPAN_YEAR+1] = NUL;

    memcpy(track->comment,header+INDEX_START_COMMENT,INDEX_SPAN_COMMENT);
    track->comment[INDEX_SPAN_COMMENT+1] = NUL;

    track->genre = header[INDEX_START_GENRE];

    return OK;
}

/*devuelve distintos valores si la cadena del primer argumento es de mayor, menor, o igual que la otra. Los valores*/
/*serán int > 0, int < 0 y 0 respectivamente. */

int ADT_Track_compare_by_title(const ADT_Track_t *track_1, const ADT_Track_t *track_2)   
{
	if( track_1 == NULL || track_2 == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	return strcmp_optimized(track_1->title, track_2->title); 
}

int ADT_Track_compare_by_artist(const ADT_Track_t *track_1, const ADT_Track_t *track_2)
{
	if( track_1 == NULL || track_2 == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	return strcmp_optimized(track_1->artist, track_2->artist);
}  

int ADT_Track_compare_by_album(const ADT_Track_t *track_1, const ADT_Track_t *track_2)
{
	if( track_1 == NULL || track_2 == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	return strcmp_optimized(track_1->album, track_2->album);
} 


int ADT_Track_compare_by_year(const ADT_Track_t *track_1, const ADT_Track_t *track_2)
{
	size_t aux_1, aux_2;
	char *temp;	

	if( track_1 == NULL || track_2 == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	aux_1 = strtoul(track_1->year, &temp, 10);
	aux_2 = strtoul(track_2->year, &temp, 10);

	return aux_1 - aux_2;
}	

int str_compare_optimized(const char *str_1, const char *str_2)
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
					return char_1 - char_2;
				}
				return -1;
			}

			if(isalnum(char_2))
			{
				return 1;
			}
			return char_1 - char_2;
		}
	}
	return 0;
}

status_t ADT_Track_print_as_csv(ADT_Track_t *track, const char *delimiter, FILE * fo)
{
	if(track == NULL || fo == NULL || delimiter == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	fprintf(fo, "%s%c%s%c%s%c%s",track->title,*delimiter,track->artist,*delimiter,genres[(int)track->genre],*delimiter,track->year);

	return OK;
}

status_t ADT_Track_print_as_xml(ADT_Track_t *track, const size_t *init_tab, FILE *fo )
{	
	size_t c;
	char aux_tabs[AUX_SIZE];

	if(track == NULL || fo == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if(*init_tab)
	{
		for(c = 0; c < *init_tab; c++)
		{
			aux_tabs[c] = HT;
		}
		aux_tabs[c] = NUL;
	}
	else 
	{
		aux_tabs[0] = NUL;
	}

	fprintf(fo, "%s%s\n"      , aux_tabs, TAG_START_TRACK);
	fprintf(fo, "%s%c%s%s%s\n", aux_tabs, TRACK_FIRST_BRANCH_TAB, TAG_START_TITLE, track->title, TAG_END_TITLE);
	fprintf(fo, "%s%c%s%s%s\n", aux_tabs, TRACK_FIRST_BRANCH_TAB, TAG_START_ARTIST, track->artist, TAG_END_ARTIST );
	fprintf(fo, "%s%c%s%s%s\n", aux_tabs, TRACK_FIRST_BRANCH_TAB, TAG_START_GENRE, genres[(int)track->genre], TAG_END_GENRE);
	fprintf(fo, "%s%c%s%s%s\n", aux_tabs, TRACK_FIRST_BRANCH_TAB, TAG_START_YEAR, track->year, TAG_END_YEAR);
	fprintf(fo, "%s%s"	  	  , aux_tabs, TAG_END_TRACK);

	return OK;	
}