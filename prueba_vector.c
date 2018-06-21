
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


/* cambiar el void por el tipo que quiero */
/* typedef status_t (*destructor_t)(void *);   */


typedef status_t (*destructor_t)(int *);

status_t delete_numbers(int * number);

destructor_t destructors[MAX_FUNCTIONS] = {
	delete_numbers
};




int main(void)
{
	ADT_Vector_t * vector;


	ADT_Vector_new(&vector);

	ADT_Vector_delete(&vector, delete_numbers);

	return EXIT_SUCCESS;
}


status_t delete_numbers(int * number)
{
	free(number);
	number = NULL;
	return OK;
}