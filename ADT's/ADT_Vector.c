#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 50
#define LF 		  '\n'
/****************************TYPEDEF'S****************************/

typedef enum 
{	
	OK,
	ERROR_NULL_POINTER,
	ERROR_NO_MEMORY,
	ERROR_NO_COMPARATOR_SETTED,
	ERROR_NO_PRINTER_SETTED,
	ERROR_NO_CONTEXT_SETTED

} status_t;

typedef int  (*comparator_t) (const void * , const void *);/*Si el primer argumento es mayor, menor o igual al segundo*//*debe devolver 1 -1 y 0 respectivamente */
typedef void (*destructor_t) (const void *);
typedef void (*printer_t)    (const void *, void *, FILE *);


typedef struct
{
    void  *context;
	void **heap;
	size_t len;	/*Tamaño efectivo del vector*/
	size_t alloc_size; /*tamaño real del vector*/ 

	destructor_t  destructor;
	comparator_t  comparator;
	printer_t 	  printer;

} ADT_Vector_t;

/****************************TYPEDEF'S****************************/


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


/*Ordena los elementos del arreglo de menor a mayor, algoritmo utilizado: bubble-sort. Hace falta darle una funcion
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
