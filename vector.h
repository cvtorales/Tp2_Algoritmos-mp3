# ifndef VECTOR__H
# define VECTOR__H
# include <stdio.h>
# include "errors.h"

# define INIT_CHOP 30
# define CHOP_SIZE 10

typedef struct 
{
	void ** elements;
	size_t size;
	size_t alloc_size;
} ADT_Vector_t;

status_t ADT_Vector_new (ADT_Vector_t ** ADT_Vector);
status_t ADT_Vector_destroy (ADT_Vector_t ** ADT_Vector, status_t (*pf) (void *));
status_t ADT_Vector_set_next_element (ADT_Vector_t ** ADT_Vector, status_t (*pointer_to_function) (const void *, void *), void * pvoid);

# endif
