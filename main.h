# ifndef MAIN__H
# define MAIN__H

# include <stdio.h>
# include "errors.h"
# include "setup.h"
# define CMD_ARG_POSITION_FIRST_MP3_FILE 7
# define CMD_ARG_POSITION_FLAG_FORMAT 1
# define CMD_ARG_POSITION_FORMAT 2
# define CMD_ARG_POSITION_FLAG_SORT 3
# define CMD_ARG_POSITION_SORT 4
# define CMD_ARG_POSITION_FLAG_OUTPUT_FILE 5
# define CMD_ARG_POSITION_OUTPUT_FILE 6
# define CMD_ARG_FLAG_FORMAT "-fmt"
# define CMD_ARG_CSV_FORMAT "csv"
# define CMD_ARG_XML_FORMAT "xml"
# define CMD_ARG_FLAG_SORT "-sort"
# define CMD_ARG_NAME_SORT "name"
# define CMD_ARG_ARTIST_SORT "artist"
# define CMD_ARG_GENRE_SORT "genre"
# define CMD_ARG_FLAG_OUTPUT_FILE "-out"

status_t validate_arguments (int argc, char * argv [], track_list_format_t * track_list_format, 
	track_sort_type_t * track_sort_type, size_t * mp3_files_quantity );
status_t validate_format_argument (char * argv [], track_list_format_t * track_list_format);
status_t validate_sort_argument (char * argv [], track_sort_type_t * track_sort_type);

# endif