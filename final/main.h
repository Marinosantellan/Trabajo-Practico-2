#ifndef MAIN_H
#define MAIN_H

#define CMD_ARG_MP3_FILE_START 7
#define MIN_CMD_ARGS 8

#define CMD_ARG_FMT_TOKEN 		  "-fmt"
#define CMD_ARG_SORT_TOKEN 		  "-sort"
#define CMD_ARG_OUTPUT_FILE_TOKEN "-out" 

#define CMD_ARG_PRINTER_FORMAT_CSV "csv"
#define CMD_ARG_PRINTER_FORMAT_XML "xml"

#define MAX_PRINTERS   2



status_t load_mp3(char* argv[] , int argc, ADT_Vector_t *vector);
status_t validate_cla(char* argv[], int argc, char **fmt_reference, char **sort_reference, char **name_fo);

#endif