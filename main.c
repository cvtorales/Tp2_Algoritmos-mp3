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

int main (int argc, char * argv [])
{
	status_t st;
	FILE * file_track_list;
	FILE * file_mp3;
	track_list_format_t track_list_format;
	track_sort_type_t track_sort_type;
	destructor_t destructor;
	clone_t clone;
	ADT_Vector_t * ADT_Vector;
	ADT_Track_t ADT_Track;
	size_t mp3_file_index;
	size_t mp3_files_quantity;
	context_t context;
	printer_t printers [NUMBER_OF_PRINTERS_FUNCTIONS] =
	{
		ADT_Track_export_as_csv,
		ADT_Track_export_as_xml,
	};
	comparer_t comparers [NUMBER_OF_COMPARATORS_FUNCTIONS ] =
	{
		ADT_Track_compare_by_name,
		ADT_Track_compare_by_artist,
		ADT_Track_compare_by_genre,
	};	


	clone = ADT_Track_clone;
	destructor = ADT_Track_destroy;
	if ((st = validate_arguments (argc, argv, &track_list_format, &track_sort_type, &mp3_files_quantity )) != OK)
	{
		print_error_msg (st);
		return st;	
	}
	if ((st = set_context (&context, mp3_files_quantity)) != OK)
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
	for (mp3_file_index = 0; mp3_file_index < mp3_files_quantity; mp3_file_index ++)
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
		if ((st = ADT_Vector_set_element (&ADT_Vector, clone, &ADT_Track, mp3_file_index)) != OK)
		{
			ADT_Vector_destroy (&ADT_Vector, destructor);
			print_error_msg (st);
			fclose (file_track_list);
			fclose (file_mp3);
			return st;	
		}
		fclose (file_mp3);
	}
	if ((st = ADT_Vector_sort (&ADT_Vector, comparers [track_sort_type])) != OK)
	{
		ADT_Vector_destroy (&ADT_Vector, destructor);
		print_error_msg (st);
		fclose (file_track_list);
		return st;	
	}

	if ((st = ADT_Vector_export (ADT_Vector, &context, file_track_list, printers [track_list_format])) != OK)
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


status_t set_context (context_t * context, const size_t mp3_files_quantity)
{
	char xml_context_tags [XML_NUMBER_OF_TAG + 1][XML_MAX_TAG_LENGTH + 1 ] =
	{
		XML_PROCESSING_INTRUCTION,
		XML_OPEN_TRACKS_TAG,
		XML_OPEN_TRACK_TAG,
		XML_OPEN_NAME_TAG,
		XML_CLOSE_NAME_TAG,
		XML_OPEN_ARTIST_TAG,
		XML_CLOSE_ARTIST_TAG,
		XML_OPEN_YEAR_TAG,
		XML_CLOSE_YEAR_TAG,
		XML_OPEN_GENRE_TAG,
		XML_CLOSE_GENRE_TAG,
		XML_CLOSE_TRACK_TAG,
		XML_CLOSE_TRACKS_TAG,
	};
	size_t i;

	context -> csv_delimiter = CSV_DELIMITER;
	context -> xml_index = 0;
	context -> xml_close_mark = mp3_files_quantity;
	if (context == NULL)
		return ERROR_NULL_POINTER;
	for (i = 0; i < XML_NUMBER_OF_TAG + 1; ++i)
		strcpy (context -> xml_tags [i], xml_context_tags [i]);
	return OK;
}