# ifndef VECTOR__H
# define VECTOR__H

# include <stdio.h>
# include "errors.h"
# include "types.h"

# define INIT_CHOP 1
# define CHOP_SIZE 2

typedef struct 
{
	void ** elements;
	size_t size;
	size_t alloc_size;
} ADT_Vector_t;

status_t ADT_Vector_new (ADT_Vector_t ** ADT_Vector);
status_t ADT_Vector_destroy (ADT_Vector_t ** ADT_Vector, status_t (*pf) (void *));
status_t ADT_Vector_set_element (ADT_Vector_t ** ADT_Vector, void * pvoid, size_t index);

status_t ADT_Vector_export (const ADT_Vector_t * ADT_Vector, void * context, FILE * fo, 
	status_t (*pf) (const void * pvoid, const void * pcontext, FILE * fo));

status_t ADT_Vector_sort (ADT_Vector_t ** ADT_Vector, int (* pf_comparer) (const void * pvoid1, const void * pvoid2));

# endif
