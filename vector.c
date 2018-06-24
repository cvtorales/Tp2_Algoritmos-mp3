# include <stdio.h>
# include <stdlib.h>
# include "errors.h"
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

status_t ADT_Vector_set_next_element (ADT_Vector_t ** ADT_Vector, status_t (*pf) (const void *, void *), void * pvoid)
{
	status_t st;
	size_t i = (*ADT_Vector) -> alloc_size;

	if (pf == NULL || ADT_Vector == NULL)
		return ERROR_NULL_POINTER;
	/* if size == alloc size blablabla

	 REALLOC */
	st = (*pf) (pvoid, (*ADT_Vector) -> elements [i]);
	if (st != OK)
		return st;

	return OK;
}