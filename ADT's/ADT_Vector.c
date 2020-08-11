#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 100

typedef struct
{

	void **elements;
	size_t len;	/*Tamaño efectivo del arreglo*/
	size_t alloc_size; /*tamaño real del arreglo*/ /*dejar el alloc_size  ...*/

	destructor_t destructor;
	comparator_t comparator;
	printer_t 	 printer;

} ADT_Vector_t;

/*Función que crea un ADT_Vector_t y se lo asigna al puntero recibido
  el vector devuelto ya tiene memoria pedida e inicializada por default*/
status_t ADT_Vector_create( ADT_Vector_t **vector)/*En realidad devuelve un ADT_Error_t*/
{
	size_t aux_size;

	if( vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if((*vector = (ADT_Vector_t*) malloc(sizeof(ADT_Vector_t))) == NULL )
	{
		return ERROR_NO_MEMORY;
	}

	aux_size = INIT_SIZE;

	if(((*vector)->elements = (void **) calloc( aux_size , sizeof(void *))) == NULL)
	{
		ADT_Vector_destroy(vector);
		return ERROR_NO_MEMORY;
	}


	(*vector)->len = 0;
	(*vector)->alloc_size = aux_size;

	(*vector)->destructor = NULL;
	(*vector)->comparator = NULL;
	(*vector)->printer    = NULL; 

	return OK;
}

status_t ADT_Vector_destroy(ADT_Vector_t **vector)
{
	size_t i;

	if(vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	for( i = 0 ; i < (*vector)->len ; i++)
	{
		destructor(((*vector)->elements)[i]);
	}

	free(elements);

	free(*vector);

	*vector = NULL;

	return OK;
}
