/*
	Punteros a funcion:
	 Problemas con los punteros a void: hice una funcion como ejemplo para 
   el caso de punteros a int, si dejo las declaraciones como estan, no funciona.
   Funciona en caso de cambiar por el tipo correspondiente (en este caso int*), tanto en la 
   funcion que llama al puntero a funcion como en el arreglo de funciones (estan con
   comentarios arriba de cada una que necesita la modificacion).

*/

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

status_t ADT_Vector_new(ADT_Vector_t ** p)
{
	size_t i;
	if( p == NULL)
		return ERROR_NULL_POINTER;

	if((*p = (ADT_Vector_t *) malloc(sizeof(ADT_Vector_t))) == NULL)
		return ERROR_NO_MEMORY;

	if(((*p)->elements = (void **) malloc(INIT_CHOP * sizeof(void *))) == NULL)
	{
		free(*p);
		*p = NULL;
		return ERROR_NO_MEMORY;
	}

	for(i=0; i<INIT_CHOP; i++)
		(*p)->elements[i]= NULL;

	(*p) -> elements = NULL;

	(*p) -> size = (*p) -> alloc_size = 0;

	/* Inicializacion de punteros a funcion en caso de que esten dentro de la cascara  */

	return OK;
}


/* cambiar el void por el tipo que quiero */
/*status_t ADT_Vector_delete(ADT_Vector_t ** p, status_t (*pf)(void*)) */
status_t ADT_Vector_delete(ADT_Vector_t ** p, status_t (*pf)(int*))
{
	size_t i;
	status_t st;

	if(p == NULL)
		return ERROR_NULL_POINTER;

	for(i=0; i < (*p)->size; i++)
	{

	/*	Esto es para el caso en donde esta dentro de la cascara */
	/*	st = (*((*p)->destructor)) ((*p)->elements[i]);  */
	/*  Caso que hago funcionar: fuera de la cascara */

		st = (*pf) ((*p)->elements[i]);
		
		if( st != OK)
			return st;

		(*p)->elements[i] = NULL;
	}

	free((*p)->elements);
	(*p)->elements = NULL;
	free(*p);
	*p = NULL;	

	return OK;
}

