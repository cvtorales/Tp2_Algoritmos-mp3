# ifndef SETUP__H
# define SETUP__H

# include <stdio.h>

# define CSV_DELIMITER '|'
# define XML_PROCESSING_INTRUCTION "<?xml version=\"1.0\" ?>"
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

typedef enum 
{
	TRACK_LIST_FORMAT_CSV = 0,
	TRACK_LIST_FORMAT_XML = 1
} track_list_format_t;

typedef enum
{
	TRACK_SORT_BY_NAME,
	TRACK_SORT_BY_ARTIST,
	TRACK_SORT_BY_GENRE
} track_sort_type_t;

typedef struct {
		track_list_format_t track_list_format;
		track_sort_type_t track_sort_type;
		size_t mp3_files_quantity;
}config_mp3_t;

# endif