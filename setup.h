# ifndef SETUP__H
# define SETUP__H

# include <stdio.h>


# define CSV_DELIMITER '|'
# define PROCESSING_INTRUCTION "<? xml version ? '"'1.0'"' ?>"
# define PROCESSING_INTRUCTION_LENGTH 40
# define OPEN_INTRUCTION 

/*AGREGAR XML*/
typedef struct 
{
	char csv_delimiter;
} context_t;

typedef enum 
{
	TRACK_LIST_FORMAT_CSV,
	TRACK_LIST_FORMAT_XML
} track_list_format_t;

typedef enum
{
	TRACK_SORT_BY_NAME,
	TRACK_SORT_BY_ARTIST,
	TRACK_SORT_BY_GENRE
} track_sort_type_t;


# endif