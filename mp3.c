# include <stdio.h>
# include <string.h>
# include "errors.h"
# include "main.h"
# include "mp3.h"
# include "track.h"
# include "setup.h"

/* AGREGAR TDA VECTOR COMO ARGUMENTO*/
status_t get_mp3_header (FILE * file_mp3)
{
    status_t st;
    ADT_Track_t * ADT_Track;

     /*PRUEBA*/
    context_t context;
    context . csv_delimiter = CSV_DELIMITER;
    /*FIN DE PRUEBA - BORRAR LUEGO*/

    if (file_mp3 == NULL)
        return ERROR_NULL_POINTER;
    if ((st = TDA_Track_new_from_file (&ADT_Track, file_mp3)) != OK)
        return st; 

    /*PRUEBA*/
    ADT_Track_export_as_csv (ADT_Track, &context, stdout);
    /*FIN DE PRUEBA - BORRAR LUEGO*/

    if ((st = TDA_Track_destroy (&ADT_Track)) != OK)
        return st;  
    return OK;
}

