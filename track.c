# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "errors.h"
# include "mp3.h"
# include "main.h"
# include "track.h"
# include "setup.h"

status_t TDA_Track_new_from_file (ADT_Track_t ** ADT_Track, FILE * file_mp3)
{
    size_t length;
    char * temp;
    char header[MP3_HEADER_SIZE];
    char buf[MP3_HEADER_SIZE];

    if (file_mp3 == NULL || ADT_Track == NULL)
       return ERROR_NULL_POINTER;
    fseek(file_mp3, 0, SEEK_END);                      /* manda el puntero al final del archivo    */
    length=ftell(file_mp3);                            /* da la distancia al comienzo              */
    fseek(file_mp3,length-MP3_HEADER_SIZE,SEEK_SET);   /* se para en el header MP3                 */
    fread(header,sizeof(char), MP3_HEADER_SIZE, file_mp3);
    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    strcpy ((*ADT_Track) -> name, buf);
    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    strcpy ((*ADT_Track) -> artist, buf);
    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    (*ADT_Track) -> year = strtol (buf, &temp, 10);
    if (*temp)
    	return ERROR_CORRUPTED_FILE;
    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    (*ADT_Track) -> genre = buf [0];
    return OK;
}

status_t TDA_Track_destroy (ADT_Track_t ** ADT_Track)
{
	if (ADT_Track == NULL)
		return ERROR_NULL_POINTER;
	strcpy ((*ADT_Track) -> name, DEFAULT_TRACK_NAME);
	strcpy ((*ADT_Track) -> artist, DEFAULT_TRACK_ARTIST);
	(*ADT_Track) -> year = DEFAULT_TRACK_YEAR;
	(*ADT_Track) -> genre = Other;
	ADT_Track = NULL;
	return OK;
}

/*Precondición: pv1 y pv2 no pueden ser NULL.*/
int ADT_Track_compare_by_name (const void * pv1, const void * pv2)
{
	ADT_Track_t * p1;
	ADT_Track_t * p2;

	if (pv1 == NULL || pv2 == NULL)
		return ERROR_NULL_POINTER;
	p1 = (ADT_Track_t *) pv1;
	p2 = (ADT_Track_t *) pv2;
	return strcmp (p1 -> name, p2 -> name);
}

/*Precondición: pv1 y pv2 no pueden ser NULL.*/
int ADT_Track_compare_by_artist (const void * pv1, const void * pv2)
{
	ADT_Track_t * p1;
	ADT_Track_t * p2;

	if (pv1 == NULL || pv2 == NULL)
		return ERROR_NULL_POINTER;
	p1 = (ADT_Track_t *) pv1;
	p2 = (ADT_Track_t *) pv2;
	return strcmp (p1 -> artist, p2 -> artist);
}

/*Precondición: pv1 y pv2 no pueden ser NULL.*/
int ADT_Track_compare_by_year (const void * pv1, const void * pv2)
{
	ADT_Track_t * p1;
	ADT_Track_t * p2;

	if (pv1 == NULL || pv2 == NULL)
		return ERROR_NULL_POINTER;
	p1 = (ADT_Track_t *) pv1;
	p2 = (ADT_Track_t *) pv2;
	return p1 -> year - p2 -> year;
}

/*Precondición: pv1 y pv2 no pueden ser NULL.*/
int ADT_Track_compare_by_genre (const void * pv1, const void * pv2)
{
	ADT_Track_t * p1;
	ADT_Track_t * p2;

	if (pv1 == NULL || pv2 == NULL)
		return ERROR_NULL_POINTER;
	p1 = (ADT_Track_t *) pv1;
	p2 = (ADT_Track_t *) pv2;
	return p1 -> genre - p2 -> genre;
}

status_t ADT_Track_export_as_csv (const void * pv, const void * pcontext, FILE * fo)
{
	ADT_Track_t * p;
	context_t * context;

	if (pv == NULL || pcontext == NULL || fo == NULL)
		return ERROR_NULL_POINTER;
	p = (ADT_Track_t *) pv;
	context = (context_t *) pcontext;
	fprintf (fo,"%s%c%s%c%hu%c%i\n", p -> name, context -> csv_delimiter, p-> artist,
	 context -> csv_delimiter, p-> year, context -> csv_delimiter ,p-> genre);
	return OK;
}

