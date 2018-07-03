# ifndef TYPES__H
# define TYPES__H

# include <stdio.h>
# include "errors.h"
# include "vector.h"

typedef char * string;
typedef unsigned short ushort;

typedef enum
{
	TRUE,
	FALSE
} bool_t;


typedef status_t (* destructor_t) (void *);
typedef status_t (* clone_t ) (const void *, void ** );
typedef status_t (* exporter_t) (const void * pvoid, const void * pcontext, FILE * fo);
typedef int (* comparator_t) (const void * pvoid1, const void * pvoid2);

# endif