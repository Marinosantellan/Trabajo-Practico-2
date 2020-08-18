#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include "errors.h"

#define INIT_SIZE 50
#define LF 		  '\n'


/****************************TYPEDEF'S****************************/
typedef int  (*comparator_t) (const void * , const void *);/*Si el primer argumento es mayor, menor o igual al segundo debe devolver int>0 int<0 y 0 respectivamente */
typedef void (*destructor_t) (const void *);
typedef void (*printer_t)    (const void *, void *, FILE *);/*el primer puntero es al objeto a imprimir y el segundo argumento es un puntero al context*/

typedef struct
{
	void **heap;
	size_t len;	/*Tamaño efectivo del vector*/
	size_t alloc_size; /*tamaño real del vector*/ 

    void *context;
	char *header;
	char *footer;
	destructor_t  destructor;
	comparator_t  comparator;
	printer_t 	  printer;

} ADT_Vector_t;
/****************************TYPEDEF'S****************************/

/************************************PROTOTIPOS************************************/
status_t 		ADT_Vector_create(ADT_Vector_t **);
status_t 		ADT_Vector_destroy(ADT_Vector_t **);
status_t 		ADT_Vector_append(ADT_Vector_t *, const void *);
status_t 		ADT_Vector_sort(const ADT_Vector_t *); 
status_t 		ADT_Vector_set_destructor(ADT_Vector_t *, destructor_t);
status_t 		ADT_Vector_set_printer(ADT_Vector_t *, printer_t);
status_t 		ADT_Vector_set_comparator(ADT_Vector_t *, comparator_t);
status_t 		ADT_Vector_set_context(ADT_Vector_t *, void *);
status_t 		ADT_Vector_set_header(ADT_Vector_t *, char *);
status_t		ADT_Vector_set_footer(ADT_Vector_t *, char *);
size_t   		ADT_Vector_get_true_size(const ADT_Vector_t *);
size_t   		ADT_Vector_get_used_size(const ADT_Vector_t *);
status_t 		ADT_Vector_export_as_csv(const ADT_Vector_t *, FILE *);
status_t 		ADT_Vector_export_as_xml(const ADT_Vector_t *, FILE *);
/************************************PROTOTIPOS************************************/

#endif