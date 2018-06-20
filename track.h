# ifndef TRACK__H
# define TRACK__H
# include <stdio.h>
# include "mp3.h"
# include "errors.h"
# define MAX_TRACK_NAME_LENGTH 31
# define MAX_TRACK_ARTIST_LENGTH 31
# define DEFAULT_TRACK_NAME "Unknown"
# define DEFAULT_TRACK_ARTIST "Unknown"
# define DEFAULT_TRACK_YEAR 1900

typedef struct 
{
	char name [MAX_TRACK_NAME_LENGTH];
	char artist [MAX_TRACK_ARTIST_LENGTH];
	ushort year;
	track_genre_t genre;
} ADT_Track_t;

status_t TDA_Track_new_from_file (ADT_Track_t ** ADT_Track, FILE * file_mp3);
status_t TDA_Track_destroy (ADT_Track_t ** ADT_Track);
int ADT_Track_compare_by_name (const void * pv1, const void * pv2);
int ADT_Track_compare_by_artist (const void * pv1, const void * pv2);
int ADT_Track_compare_by_year (const void * pv1, const void * pv2);
int ADT_Track_compare_by_genre (const void * pv1, const void * pv2);
status_t ADT_Track_export_as_csv (const void * pv, const void * pcontext, FILE * fo);

# endif
