# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "errors.h"
# include "mp3.h"
# include "main.h"
# include "track.h"
# include "setup.h"

status_t ADT_Track_new_from_file (void * pvoid, FILE * file_mp3)
{
    size_t length;
    char * temp;
    char header[MP3_HEADER_SIZE];
    char buf[MP3_HEADER_SIZE];
    ADT_Track_t * ptrack;

    if (file_mp3 == NULL || pvoid == NULL)
       return ERROR_NULL_POINTER;
  	ptrack = (ADT_Track_t *) pvoid;
    fseek(file_mp3, 0, SEEK_END);                      /* manda el puntero al final del archivo    */
    length=ftell(file_mp3);                            /* da la distancia al comienzo              */
    fseek(file_mp3,length-MP3_HEADER_SIZE,SEEK_SET);   /* se para en el header MP3                 */
    fread(header,sizeof(char), MP3_HEADER_SIZE, file_mp3);
    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    strcpy (ptrack -> name, buf);
    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    strcpy (ptrack -> artist, buf);
    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    ptrack -> year = strtol (buf, &temp, 10);
    if (*temp)
    	return ERROR_CORRUPTED_FILE;
    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    ptrack -> genre = buf [0];
    return OK;
}

status_t ADT_Track_destroy (void * pvoid)
{
	ADT_Track_t * ptrack;

	if (pvoid == NULL)
		return ERROR_NULL_POINTER;
	ptrack = (ADT_Track_t *) pvoid;
	strcpy (ptrack -> name, DEFAULT_TRACK_NAME);
	strcpy (ptrack -> artist, DEFAULT_TRACK_ARTIST);
	ptrack -> year = DEFAULT_TRACK_YEAR;
	ptrack -> genre = Other;
	free (ptrack);
	ptrack = NULL;
	return OK;
}

/*Precondición: pvoid1 no puede ser NULL.*/
status_t ADT_Track_clone (const void * pvoid1, void ** pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t ** ptrack2;

	if (pvoid1 == NULL)
		return ERROR_NULL_POINTER;
	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t **) pvoid2;
	if ((*ptrack2 = (ADT_Track_t *) malloc (sizeof (ADT_Track_t))) == NULL)
    	return ERROR_NO_MEMORY;
	strcpy ( (*ptrack2) -> name, ptrack1 -> name);
	strcpy ( (*ptrack2) -> artist, ptrack1 -> artist);
	(*ptrack2) -> year = ptrack1 -> year;
	(*ptrack2) -> genre = ptrack1 -> genre;
	return OK;
}


/*Precondición: pvoid1 y pvoid2 no pueden ser NULL.*/
int ADT_Track_compare_by_name (const void * pvoid1, const void * pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t * ptrack2;

	if (pvoid1 == NULL || pvoid2 == NULL)
		return ERROR_NULL_POINTER;
	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t *) pvoid2;
	return strcmp (ptrack1 -> name, ptrack2 -> name);
}

/*Precondición: pvoid1 y pvoid2 no pueden ser NULL.*/
int ADT_Track_compare_by_artist (const void * pvoid1, const void * pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t * ptrack2;

	if (pvoid1 == NULL || pvoid2 == NULL)
		return ERROR_NULL_POINTER;
	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t *) pvoid2;
	return strcmp (ptrack1 -> artist, ptrack2 -> artist);
}

/*Precondición: pvoid1 y pvpid2 no pueden ser NULL.*/
int ADT_Track_compare_by_year (const void * pvoid1, const void * pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t * ptrack2;

	if (pvoid1 == NULL || pvoid2 == NULL)
		return ERROR_NULL_POINTER;
	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t *) pvoid2;
	return ptrack1 -> year - ptrack2 -> year;
}

/*Precondición: pvoid1 y pvpid2 no pueden ser NULL.*/
int ADT_Track_compare_by_genre (const void * pvoid1, const void * pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t * ptrack2;

	if (pvoid1 == NULL || pvoid2 == NULL)
		return ERROR_NULL_POINTER;
	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t *) pvoid2;
	return ptrack1 -> genre - ptrack2 -> genre;
}


/* NOTA: FALTA AGREGAR DICCIONARIO DE GENEROS*/
status_t ADT_Track_export_as_csv (const void * pvoid, const void * pcontext, FILE * fo)
{
	ADT_Track_t * ptrack;
	context_t * context;

	if (pvoid == NULL || pcontext == NULL || fo == NULL)
		return ERROR_NULL_POINTER;
	ptrack = (ADT_Track_t *) pvoid;
	context = (context_t *) pcontext;
	fprintf (fo,"%s%c%s%c%hu%c%i\n", ptrack -> name, context -> csv_delimiter, ptrack -> artist,
		context -> csv_delimiter, ptrack -> year, context -> csv_delimiter ,ptrack-> genre);
	return OK;
}

/* NOTA: FALTA AGREGAR DICCIONARIO DE GENEROS*/
status_t ADT_Track_export_as_xml (const void * pvoid, const void * pcontext, FILE * fo)
{
	size_t i;
	ADT_Track_t * ptrack;
	context_t * context;
	
	if (pvoid == NULL || pcontext == NULL || fo == NULL)
		return ERROR_NULL_POINTER;
	ptrack = (ADT_Track_t *) pvoid;
	context = (context_t *) pcontext;
	
	if (context -> xml_index == 0)
	{
		for (i = 0; i < 2; ++i)
			fprintf (fo, "%s\n" ,context -> xml_tags [i]);
	}
	context -> xml_index ++;
	i = 2;
	fprintf (fo, "\t%s\n" ,context -> xml_tags [i]);
	i ++ ;
	fprintf (fo, "\t\t%s %s %s\n" ,context -> xml_tags [i], ptrack -> name,  context -> xml_tags [i + 1]);
	i += 2;
	fprintf (fo, "\t\t%s %s %s\n" ,context -> xml_tags [i], ptrack -> artist,  context -> xml_tags [i + 1]);
	i += 2;
	fprintf (fo, "\t\t%s %hu %s\n" ,context -> xml_tags [i], ptrack -> year,  context -> xml_tags [i + 1]);
	i += 2;
	fprintf (fo, "\t\t%s %i %s\n" ,context -> xml_tags [i], ptrack -> genre,  context -> xml_tags [i + 1]);
	i += 2;
	fprintf (fo, "%s\n" , context -> xml_tags [i]);
	i ++;
	if (context -> xml_index == context -> xml_close_mark)
		fprintf (fo, "%s\n" , context -> xml_tags [i]);
	return OK;
}


