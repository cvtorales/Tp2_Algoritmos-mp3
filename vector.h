	#ifndef VECTOR__H
	#define VECTOR__H

	#include <stdio.h>

#define INIT_CHOP 10
#define MAX_FUNCTIONS 1

typedef enum{
				OK = 0,
				ERROR_NULL_POINTER = 1,
				ERROR_NO_MEMORY
			}status_t;

typedef struct 
{
	void ** elements;
	size_t size;
	size_t alloc_size;
	
}ADT_Vector_t;


status_t ADT_Vector_new(ADT_Vector_t ** p);
/* cambiar el void por el tipo que quiero */
/*status_t ADT_Vector_delete(ADT_Vector_t ** p, status_t (*pf)(void*));  */
status_t ADT_Vector_delete(ADT_Vector_t ** p, status_t (*pf)(int*));

	#endif