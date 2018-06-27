# ifndef SETUP__H
# define SETUP__H

# include <stdio.h>

# define CSV_DELIMITER '|'
# define XML_PROCESSING_INTRUCTION "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
# define XML_MAX_TAG_LENGTH 40
# define XML_NUMBER_OF_TAG 12
# define XML_OPEN_TRACKS_TAG "<Tracks>"
# define XML_CLOSE_TRACKS_TAG "</Tracks>"
# define XML_OPEN_TRACK_TAG "<Track>"
# define XML_CLOSE_TRACK_TAG "</Track>"
# define XML_OPEN_NAME_TAG "<Name>"
# define XML_CLOSE_NAME_TAG "</Name>"
# define XML_OPEN_ARTIST_TAG "<Artist>"
# define XML_CLOSE_ARTIST_TAG "</Artist>"
# define XML_OPEN_YEAR_TAG "<Year>"
# define XML_CLOSE_YEAR_TAG "</Year>"
# define XML_OPEN_GENRE_TAG "<Genre>"
# define XML_CLOSE_GENRE_TAG "</Genre>"

typedef struct
{
	char csv_delimiter;
	size_t xml_index;
	size_t xml_close_mark;
	char xml_tags [XML_NUMBER_OF_TAG + 1][XML_MAX_TAG_LENGTH + 1];
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