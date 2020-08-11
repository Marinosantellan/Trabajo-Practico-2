#include <stdio.h>
#include <stdlib.h>

typedef enum 
{
	ERROR_NULL_POINTER,
	ERROR_NO_MEMORY,
	OK

}status_t;

#define INIT_SIZE 50

typedef struct
{

	void **heap;
	size_t len;	/*Tamaño efectivo del vector*/
	size_t alloc_size; /*tamaño real del vector*/ 

	destructor_t destructor;
	comparator_t comparator;
	printer_t 	 printer;

} ADT_Vector_t;

/*Función que crea un ADT_Vector_t y se lo asigna al puntero recibido
  el vector devuelto ya tiene memoria pedida e inicializada con espacio para INIT_SIZE elementos*/
status_t ADT_Vector_create( ADT_Vector_t **vector)
{

	if( vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if((*vector = (ADT_Vector_t*) malloc(sizeof(ADT_Vector_t))) == NULL )
	{
		return ERROR_NO_MEMORY;
	}

	if(((*vector)->heap = (void **) calloc( INIT_SIZE , sizeof(void *))) == NULL)
	{
		free(*vector);
		*vector = NULL;
		return ERROR_NO_MEMORY;
	}


	(*vector)->len = 0;
	(*vector)->alloc_size = INIT_SIZE;

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
		destructor(((*vector)->heap)[i]);
	}

	free(heap);

	free(*vector); 
	*vector = NULL;

	return OK;
}

/*Función que inserta un elemento al final del vector. En caso de que no haya mas espacio en este, se pedirá mas*/
/*Si ocurre cualquier error el vector se destruye pero su respectivo puntero NO se inializa a NULL*/
status_t ADT_Vector_append(ADT_Vector_t *vector, const void *ptr_obj)
{
	void *aux_ptr; 

	if (vector == NULL || ptr_obj == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if(vector->len == vector->alloc_size)
	{
		if( ((aux_ptr = (void *) realloc( vector->heap , 2*(vector->alloc_size)) ) == NULL))
		{
			ADT_Vector_destroy(&vector);
			return ERROR_NO_MEMORY;
		}

		vector->heap = aux_ptr;

		(vector->alloc_size)*=2;
	}

	(vector->heap)[vector->len] = (void *) ptr_obj;

	vector->len++;

	return OK;
}

status_t 

size_t ADT_Vector_get_true_size( const ADT_Vector_t *vector)
{
	return vector->alloc_size;
}

size_t ADT_Vector_get_used_size(const ADT_Vector_t *vector)
{
	return vector->len;
}
