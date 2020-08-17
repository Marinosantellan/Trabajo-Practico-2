#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/*Función que crea un ADT_Vector_t y se lo asigna al puntero recibido
el vector devuelto ya tiene memoria pedida e inicializada con espacio para INIT_SIZE elementos*/
status_t ADT_Vector_create(ADT_Vector_t **vector)
{

	if(vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if((*vector = (ADT_Vector_t*) malloc(sizeof(ADT_Vector_t))) == NULL)
	{
		return ERROR_NO_MEMORY;
	}

	if(((*vector)->heap = (void **) calloc(INIT_SIZE, sizeof(void *))) == NULL)
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
	(*vector)->context    = NULL;
	(*vector)->header     = NULL;
	(*vector)->footer     = NULL;

	return OK;
}
/*Que pasa si llamamos a esta funcion para poner en nulo a un vector que ya esta destruido???*/
status_t ADT_Vector_destroy(ADT_Vector_t **vector) 
{
	size_t i;

	if(vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	for( i = 0 ; i < (*vector)->len ; i++)
	{
		((*vector)->destructor)(((*vector)->heap)[i]);
	}

	free((*vector)->heap);

	free(*vector); 
	*vector = NULL;

	return OK;
}
/*******************************SETTERS*******************************/

status_t ADT_Vector_set_destructor(ADT_Vector_t *vector, destructor_t destructor)
{
	if(vector == NULL || destructor == NULL)
	{
		return ERROR_NULL_POINTER;
	}	
	vector->destructor = destructor;
	return OK;
}

status_t ADT_Vector_set_printer(ADT_Vector_t *vector, printer_t printer)
{
	if(vector == NULL || printer == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	vector->printer = printer;
	return OK;
}

status_t ADT_Vector_set_comparator(ADT_Vector_t *vector, comparator_t comparator)
{
	if(vector == NULL || comparator == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	vector->comparator = comparator;
	return OK;
}

status_t ADT_Vector_set_context(ADT_Vector_t *vector, void *context)
{
	if(vector == NULL || context == NULL)
	{
		return ERROR_NULL_POINTER;
	}	
	vector->context = context;
	return OK;
}

status_t ADT_Vector_set_header(ADT_Vector_t *vector, char *header)
{
	if(vector == NULL || header == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	vector->header = header;
	return OK;
}

status_t ADT_Vector_set_footer(ADT_Vector_t *vector, char *footer)
{
	if(vector == NULL || footer == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	vector->footer = footer;
	return OK;
}
/*******************************SETTERS*******************************/



/*******************************GETTERS*******************************/

size_t ADT_Vector_get_true_size(const ADT_Vector_t *vector)
{
	return vector->alloc_size;
}

size_t ADT_Vector_get_used_size(const ADT_Vector_t *vector)
{
	return vector->len;
}

/*******************************GETTERS*******************************/



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
		if(((aux_ptr = (void *) realloc(vector->heap, 2*(vector->alloc_size))) == NULL))
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


/*Ordena los elementos del arreglo de menor a mayor, algoritmo utilizado: insection-sort. Hace falta brindarle una funcion
	que compare el tipo de dato que almacena*/
status_t ADT_Vector_sort(const ADT_Vector_t *vector)
{
	size_t i,j;
	void *index;

	if(vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}

	if(vector->comparator == NULL)
	{
		return ERROR_NO_COMPARATOR_SETTED;
	}

	for(i = 1; i < vector->len; i++ )
	{	
		index = (vector->heap)[i];

		for(j = i; j > 0; j--)
		{
			if((*vector->comparator)(index, (vector->heap)[j-1] ) == -1 )
			{
				(vector->heap)[j] = (vector->heap)[j-1];
			}
			else
			{
				break;
			} 		
		}
		(vector->heap)[j] = index;
	}	
	return OK;
}

status_t ADT_Vector_export_as_csv(const ADT_Vector_t *vector, FILE *fo)
{
	size_t i;

	if(fo == NULL || vector == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	if(vector->printer == NULL)
	{
		return ERROR_NO_PRINTER_SETTED;
	}
	if(vector->context == NULL)
	{
		return ERROR_NO_CONTEXT_SETTED;
	}

	for(i = 0; i < vector->len ; i++)
	{
		(*vector->printer)((vector->heap)[i], vector->context, fo);
		putchar(LF);
	}
	return OK;
}

status_t ADT_Vector_export_as_xml(const ADT_Vector_t *vector, FILE *fo)
{
	size_t i;

	if(vector == NULL || fo == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	if(vector->printer == NULL)
	{
		return ERROR_NO_PRINTER_SETTED;
	}
	if(vector->header == NULL)
	{
		return ERROR_NO_HEADER_SETTED;
	}
	if(vector->footer == NULL)
	{
		return ERROR_NO_FOOTER_SETTED;
	}

	fprintf(fo, "%s\n", vector->header);

	for( i = 0; i < vector->len; i++)
	{
		(*vector->printer)((vector->heap)[i], vector->context, fo);
		putchar(LF);
	}

	fprintf(fo, "%s", vector->footer);

	return OK;
}