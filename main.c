/***  main.c  ***/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "errors.h"
# include "types.h"
# include "main.h"
# include "setup.h"
# include "mp3.h"
# include "vector.h"
# include "track.h"
# include "tracks_printer.h"

comparator_t comparers [NUMBER_OF_COMPARATORS_FUNCTIONS ] =
{
	ADT_Track_compare_by_name,
	ADT_Track_compare_by_artist,
	ADT_Track_compare_by_genre,
};	

int main (int argc, char * argv [])
{
	status_t st;
	FILE * file_track_list;
	FILE * file_mp3;
	destructor_t destructor;
	ADT_Vector_t * ADT_Vector;
	void * ADT_Track;
	size_t mp3_file_index;
	config_mp3_t config; 

	destructor = ADT_Track_destroy;

	if ((st = validate_arguments (argc, argv, &config)) != OK)
	{
		print_error_msg (st);
		return st;	
	}

	if ((file_track_list = fopen (argv [CMD_ARG_POSITION_OUTPUT_FILE], "wt")) == NULL)
	{
		print_error_msg (ERROR_OUTPUT_FILE);
		return ERROR_OUTPUT_FILE;
	} 

	if ((st = ADT_Vector_new (&ADT_Vector)) != OK)
	{
		print_error_msg (st);
		fclose (file_track_list);
		return st;	
	}

	for (mp3_file_index = 0; mp3_file_index < config.mp3_files_quantity; mp3_file_index ++)
	{
		if ((file_mp3 = fopen (argv [mp3_file_index + CMD_ARG_POSITION_FIRST_MP3_FILE], "rb")) == NULL)
		{
			ADT_Vector_destroy (&ADT_Vector, destructor);
			print_error_msg (ERROR_INPUT_MP3_FILE);
			fclose (file_track_list);

			return ERROR_INPUT_MP3_FILE;
		}

		if ((st = ADT_Track_new_from_file (&ADT_Track, file_mp3)) != OK)
		{
			ADT_Vector_destroy (&ADT_Vector, destructor);

			print_error_msg (st);

			fclose (file_track_list);
			fclose (file_mp3);

			return st;	
		}

		if ((st = ADT_Vector_set_element (&ADT_Vector, ADT_Track, mp3_file_index)) != OK)
		{
			ADT_Vector_destroy (&ADT_Vector, destructor);
			ADT_Track_destroy(ADT_Track);

			print_error_msg (st);

			fclose (file_track_list);
			fclose (file_mp3);

			return st;	
		}

		fclose (file_mp3);
		
	}  /* Fin del ciclo for */

	if ((st = ADT_Vector_sort (&ADT_Vector, comparers [config.track_sort_type])) != OK)
	{
		ADT_Vector_destroy (&ADT_Vector, destructor);

		print_error_msg (st);

		fclose (file_track_list);

		return st;	
	}

	if ((st = export_track_vector(ADT_Vector, config.track_list_format, file_track_list)) != OK)
	{
		ADT_Vector_destroy (&ADT_Vector, destructor);

		print_error_msg (st);

		fclose (file_track_list);

		return st;	
	}

	
	if ((st = ADT_Vector_destroy (&ADT_Vector, destructor)) != OK)
	{
		print_error_msg (st);

		fclose (file_track_list);

		return st;	
	}
	
	fclose (file_track_list);

	return OK;		
}

status_t validate_arguments (int argc, char * argv [], config_mp3_t * config)
{
	status_t st;
	track_list_format_t format; 
	track_sort_type_t sort;

	if (argv == NULL || config == NULL)
		return ERROR_NULL_POINTER;

	if ((st = validate_format_argument (argv, &format)) != OK)
		return st;

	if ((st = validate_sort_argument (argv, &sort)) != OK)
		return st;

	config -> track_list_format = format;
	config -> track_sort_type = sort; 

	if (strcmp (argv [CMD_ARG_POSITION_FLAG_OUTPUT_FILE], CMD_ARG_FLAG_OUTPUT_FILE))
		return ERROR_PROG_INVOCATION;

	if (argc < CMD_ARG_POSITION_FIRST_MP3_FILE)
		return ERROR_PROG_INVOCATION;

	config -> mp3_files_quantity = argc - CMD_ARG_POSITION_FIRST_MP3_FILE;

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
