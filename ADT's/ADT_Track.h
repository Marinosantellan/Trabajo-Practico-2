#ifndef TRACK
#define TRACK

#define MP3_HEADER_SIZE 		128
#define NUL						'\0'

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

status_t 	ADT_Track_create(ADT_Track_t **track);
status_t 	ADT_Track_destroy(ADT_Track_t **track);
status_t 	ADT_Track_load(ADT_Track_t *track, FILE* fi);
int 		ADT_Track_compare_by_title(const ADT_Track_t *track_1, const ADT_Track_t *track_2);
int 		ADT_Track_compare_by_artist(const ADT_Track_t *track_1, const ADT_Track_t *track_2);
int 		ADT_Track_compare_by_album(const ADT_Track_t *track_1, const ADT_Track_t *track_2);
int 		ADT_Track_compare_by_year(const ADT_Track_t *track_1, const ADT_Track_t *track_2);
int 		str_compare_optimized(const char *str_1, const char *str_2);
status_t 	ADT_Track_export_as_CSV(ADT_Track_t *track, const char *delimiter, FILE * fo);
status_t 	ADT_Track_export_as_XML(ADT_Track_t *track, FILE *fo );


typedef enum
{
	OK,
	ERROR_NULL_POINTER,
	ERROR_NO_MEMORY

}status_t;

char *genre[] =
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

#endif
