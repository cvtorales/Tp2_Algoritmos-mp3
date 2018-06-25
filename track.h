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

typedef status_t (* destructor_t) (void *);
typedef status_t (* clone_t ) (const void *, void ** );

status_t ADT_Track_new_from_file (void * pvoid, FILE * file_mp3);
status_t ADT_Track_destroy (void * pvoid);
status_t ADT_Track_clone (const void * pvoid1, void ** pvoid2);
int ADT_Track_compare_by_name (const void * pvoid1, const void * pvoid2);
int ADT_Track_compare_by_artist (const void * pvoid1, const void * pvoid2);
int ADT_Track_compare_by_year (const void * pvoid1, const void * pvoid2);
int ADT_Track_compare_by_genre (const void * pvoid1, const void * pvoid2);
status_t ADT_Track_export_as_csv (const void * pvoid, const void * pcontext, FILE * fo);
status_t ADT_Track_export_as_xml (const void * pvoid, const void * pcontext, FILE * fo);

# endif
