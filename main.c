# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "errors.h"
# include "main.h"
# include "setup.h"
# include "mp3.h"

int main (int argc, char * argv [])
{
	FILE * file_track_list;
	FILE * file_mp3;
	track_list_format_t track_list_format;
	track_sort_type_t track_sort_type;
	status_t st;
	size_t mp3_file_index;
	size_t mp3_files_quantity;

	if ((st = validate_arguments (argc, argv, &track_list_format, &track_sort_type, &mp3_files_quantity )) != OK)
	{
		print_error_msg (st);
		return st;	
	}
	if ((file_track_list = fopen (argv [CMD_ARG_POSITION_OUTPUT_FILE], "wt")) == NULL)
	{
		print_error_msg (ERROR_OUTPUT_FILE); /* CAMBIAR*/
		return ERROR_OUTPUT_FILE;
	} 
	
	/*TDA_Vector_new () */

	for (mp3_file_index = 0; mp3_file_index < mp3_files_quantity; mp3_file_index ++)
	{
		if ((file_mp3 = fopen (argv [mp3_file_index + CMD_ARG_POSITION_FIRST_MP3_FILE], "rb")) == NULL)
		{
			print_error_msg (ERROR_INPUT_MP3_FILE);
			return ERROR_INPUT_MP3_FILE;
		}
		if ((st = get_mp3_header (file_mp3)) != OK)
		{
			print_error_msg (st);
			return st;	
		}
		fclose (file_mp3);
	}
	/*sort_mp3_list () */
	/*print_mp3_list () */
	/*TDA_Vector_destroy () */
	
	fclose (file_track_list);
	return OK;		
}

status_t validate_arguments (int argc, char * argv [], track_list_format_t * track_list_format, 
	track_sort_type_t * track_sort_type, size_t * mp3_files_quantity )
{
	status_t st;

	if (argv == NULL || track_list_format == NULL || track_sort_type == NULL || mp3_files_quantity == NULL)
		return ERROR_NULL_POINTER;
	if ((st = validate_format_argument (argv, track_list_format)) != OK)
		return st;
	if ((st = validate_sort_argument (argv, track_sort_type)) != OK)
		return st;
	if (strcmp (argv [CMD_ARG_POSITION_FLAG_OUTPUT_FILE], CMD_ARG_FLAG_OUTPUT_FILE))
		return ERROR_PROG_INVOCATION;
	if (argc < CMD_ARG_POSITION_FIRST_MP3_FILE)
		return ERROR_PROG_INVOCATION;
	*mp3_files_quantity = argc - CMD_ARG_POSITION_FIRST_MP3_FILE;
	return OK;
}

status_t validate_format_argument (char * argv [], track_list_format_t * track_list_format)
{
	if (argv == NULL || track_list_format == NULL)
		return ERROR_NULL_POINTER;
	if (strcmp (argv [CMD_ARG_POSITION_FLAG_FORMAT], CMD_ARG_FLAG_FORMAT))
		return ERROR_PROG_INVOCATION;
	if (!strcmp (argv [CMD_ARG_POSITION_FORMAT], CMD_ARG_CSV_FORMAT))
		*track_list_format = TRACK_LIST_FORMAT_CSV;
	if (!strcmp (argv [CMD_ARG_POSITION_FORMAT], CMD_ARG_XML_FORMAT))
		*track_list_format = TRACK_LIST_FORMAT_XML;
	if (*track_list_format != TRACK_LIST_FORMAT_XML && *track_list_format != TRACK_LIST_FORMAT_CSV)
		return ERROR_PROG_INVOCATION;
	return OK;
}

status_t validate_sort_argument (char * argv [], track_sort_type_t * track_sort_type)
{
	if (argv == NULL || track_sort_type == NULL)
		return ERROR_NULL_POINTER;
	if (strcmp (argv [CMD_ARG_POSITION_FLAG_SORT], CMD_ARG_FLAG_SORT))
		return ERROR_PROG_INVOCATION;
	if (!strcmp (argv [CMD_ARG_POSITION_SORT], CMD_ARG_NAME_SORT))
		*track_sort_type = TRACK_SORT_BY_NAME;
	if (!strcmp (argv [CMD_ARG_POSITION_SORT], CMD_ARG_ARTIST_SORT))
		*track_sort_type = TRACK_SORT_BY_ARTIST;
	if (!strcmp (argv [CMD_ARG_POSITION_SORT], CMD_ARG_GENRE_SORT))
		*track_sort_type = TRACK_SORT_BY_GENRE;
	if (*track_sort_type != TRACK_SORT_BY_NAME && *track_sort_type != TRACK_SORT_BY_ARTIST
	 && *track_sort_type != TRACK_SORT_BY_GENRE)
		return ERROR_PROG_INVOCATION;
	return OK;
}