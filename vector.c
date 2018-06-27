# include <stdio.h>
# include <stdlib.h>
# include "errors.h"
# include "types.h"
# include "vector.h"



status_t ADT_Vector_new ( ADT_Vector_t ** ADT_Vector)
{
	size_t i;

    if (ADT_Vector == NULL)
        return ERROR_NULL_POINTER;
    if (((*ADT_Vector) = (ADT_Vector_t*) malloc (sizeof (ADT_Vector_t))) == NULL)
    	return ERROR_NO_MEMORY;
    if (((*ADT_Vector) -> elements = (void **) malloc (INIT_CHOP * sizeof ( void *))) == NULL)
    	{
    		free (*ADT_Vector);
    		*ADT_Vector = NULL;
    		return ERROR_NO_MEMORY;
    	}
    for (i = 0; i < INIT_CHOP; i++)
    	(*ADT_Vector) -> elements [i] = NULL;
    (*ADT_Vector) -> alloc_size = 0;
    (*ADT_Vector) -> size = INIT_CHOP;
    return OK;
}

status_t ADT_Vector_destroy (ADT_Vector_t ** ADT_Vector, status_t (*pf) (void *))
{
	status_t st;
	size_t i;

	if (pf == NULL || ADT_Vector == NULL)
		return ERROR_NULL_POINTER;
	for (i = 0; i < (*ADT_Vector) -> size; ++i)
	{
		if ( (*ADT_Vector) -> elements [i] != NULL)
		{
			st = (*pf) ((*ADT_Vector) -> elements [i]);
			if (st != OK)
				return st;
			(*ADT_Vector) -> elements [i] = NULL;
		}
	}
	free ( (*ADT_Vector) -> elements);
	(*ADT_Vector) -> elements = NULL;
	free (*ADT_Vector);
	*ADT_Vector = NULL;
	return OK;
}

status_t ADT_Vector_set_element (ADT_Vector_t ** ADT_Vector, status_t (*pf) (const void *, void **), void * pvoid, size_t index)
{
	status_t st;
	void ** aux;
	
	if (pf == NULL || ADT_Vector == NULL)
		return ERROR_NULL_POINTER;
	if ((*ADT_Vector) -> alloc_size == (*ADT_Vector) -> size)
	{
		if ((aux = (void **) realloc ((*ADT_Vector) -> elements , ((*ADT_Vector) -> alloc_size + CHOP_SIZE) * sizeof ( void *))) == NULL)
			return ERROR_NO_MEMORY;
		(*ADT_Vector) -> elements = aux;
		(*ADT_Vector) -> size += CHOP_SIZE;
	}
	if ((*ADT_Vector) -> elements [index] == NULL) /*Si no hay un elemento en la posición index se suma 1 a alloc_size*/
		(*ADT_Vector) -> alloc_size ++;
	st = (*pf) (pvoid, (&(*ADT_Vector) -> elements [index]));
	if (st != OK)
		return st;
	return OK;
}

status_t ADT_Vector_export (const ADT_Vector_t * ADT_Vector, void * context, FILE * fo, status_t (*pf) (const void * pvoid, const void * pcontext, FILE * fo))
{
	status_t st;
	size_t i;

	if (pf == NULL || ADT_Vector == NULL || context == NULL)
		return ERROR_NULL_POINTER;
	for (i = 0; i < ADT_Vector -> alloc_size; ++i)
	{
		if ((st = (*pf) (ADT_Vector -> elements [i], context, fo ) != OK))
			return st;
	}
	return OK;
}

/* SELECTION SORT*/
status_t ADT_Vector_sort (ADT_Vector_t ** ADT_Vector, status_t (* pf_clone ) (const void *, void ** ) ,
	int (* pf_compare) (const void * pvoid1, const void * pvoid2))
{
	status_t st;
	size_t i, j;
	int min = 0;
	void * clone_element;

	if (pf_clone == NULL || pf_compare == NULL || ADT_Vector == NULL)
		return ERROR_NULL_POINTER;

	for (i = 0; i < (*ADT_Vector) -> alloc_size - 1; i++)
	{
		min = i;
		for (j = i + 1; j < (*ADT_Vector) -> alloc_size ; j ++)
		{
			if (((*pf_compare) ( (*ADT_Vector) -> elements [j],  (*ADT_Vector) -> elements [min]) != OK) < 0)
				min = j;
		}
		if ((st = (*pf_clone) ( (*ADT_Vector) -> elements [i], &clone_element)) != OK)
			return st;
		(*ADT_Vector) -> elements [i] = (*ADT_Vector) -> elements [min];
		(*ADT_Vector) -> elements [min] = clone_element;
	}
	return OK;
}
