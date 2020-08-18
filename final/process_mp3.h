#ifndef PROCESS_MP3_H
#define PROCESS_MP3_H

#define CMD_ARG_MP3_FILE_START			7

/************TYPEDEF'S************/
typedef enum  
{
	FMT_CSV,
	FMT_XML

}	format_t;
/************TYPEDEF'S************/

/***************************************PROTOTIPOS****************************************/
status_t	process_mp3(char* argv[], size_t ,ADT_Vector_t **, format_t , FILE*);  
status_t 	load_mp3( char* argv[] , size_t , ADT_Vector_t *);
status_t 	vector_export(ADT_Vector_t *, format_t , FILE *);
/****************************************PROTOTIPOS***************************************/

#endif