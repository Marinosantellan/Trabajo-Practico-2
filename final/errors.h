#ifndef ERRORS_H
#define ERRORS_H

#define MSG_ERROR_PREFIX "ERROR: "

typedef enum 
{
	OK,	
	ERROR_NULL_POINTER,
	ERROR_NO_MEMORY,
	ERROR_NO_DISK_MEMORY,
	ERROR_OPENING_FILE,
	ERROR_INVALID_INVOCATION,
	ERROR_INVALID_INVOCATION_FMT,
	ERROR_INVALID_INVOCATION_SORT_MODE,
	ERROR_NO_COMPARATOR_SETTED,	
	ERROR_NO_PRINTER_SETTED,
	ERROR_NO_CONTEXT_SETTED,
	ERROR_NO_HEADER_SETTED,
	ERROR_NO_FOOTER_SETTED

} status_t;

status_t show_error(status_t st);

#define MSG_ERROR_OK 						   "ok"
#define MSG_ERROR_NULL_POINTER 				   "null pointer"
#define MSG_ERROR_NO_MEMORY  				   "no memory"
#define MSG_ERROR_NO_DISK_MEMORY 			   "no enough disk memory"
#define MSG_ERROR_OPENING_FILE   			   "opening file"
#define MSG_ERROR_INVALID_INVOCATION 	  	   "invalid invocation"
#define MSG_ERROR_INVALID_INVOCATION_FMT 	   "invalid format especified at invocation"
#define MSG_ERROR_INVALID_INVOCATION_SORT_MODE "invalid sort mode especified at invocation"
#define MSG_ERROR_NO_COMPARATOR_SETTED 		   "there is no comparator function setted"
#define MSG_ERROR_NO_PRINTER_SETTED 		   "there is no printer function setted"
#define MSG_ERROR_NO_CONTEXT_SETTED 	  	   "there is no \"context\" setted"
#define MSG_ERROR_NO_HEADER_SETTED  		   "there is no header setted" 
#define MSG_ERROR_NO_FOOTER_SETTED			   "there is no footer setted"

#endif