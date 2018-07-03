# include <stdio.h>
# include <string.h>
# include "errors.h"
# include "types.h"
# include "setup.h"
# include "vector.h"
# include "track.h"
# include "mp3.h"
# include "tracks_printer.h"

extern string genres [NUMBER_OF_GENRES];


printer_t printers [NUMBER_OF_PRINTERS_FUNCTIONS] =
{
	print_vector_csv,
	print_vector_xml
};

status_t export_track_vector(const ADT_Vector_t * vector, track_list_format_t format, FILE * fo)
{
	size_t i;

	if (fo == NULL || vector == NULL )
		return ERROR_NULL_POINTER;

	for(i=0; i < NUMBER_OF_PRINTERS_FUNCTIONS; i++)
	{
	    if(i == format )
	    {
	        (*(printers[format]))(vector, fo);
	    }
	}

	return OK;
}


status_t print_header_xml(FILE * fo)
{
	if(fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo, "%s\n", XML_OPEN_TRACKS_TAG );

	return OK;
}

status_t print_footer_xml(FILE * fo)
{
	if(fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo, "%s\n", XML_CLOSE_TRACKS_TAG );

	return OK;
}

status_t print_track_xml(ADT_Track_t * track, FILE * fo)
{
	if(track == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo, "\t%s\n", XML_OPEN_TRACK_TAG);

	fprintf(fo, "\t\t%s%s%s\n", XML_OPEN_NAME_TAG, track -> name, XML_CLOSE_NAME_TAG);
	fprintf(fo, "\t\t%s%s%s\n", XML_OPEN_ARTIST_TAG, track -> artist, XML_CLOSE_ARTIST_TAG);
	fprintf(fo, "\t\t %s %hu %s\n", XML_OPEN_YEAR_TAG, track -> year, XML_CLOSE_YEAR_TAG);
	fprintf(fo, "\t\t%s%s%s\n", XML_OPEN_GENRE_TAG, genres [track -> genre], XML_CLOSE_GENRE_TAG);

	fprintf(fo, "\t%s\n", XML_CLOSE_TRACK_TAG);

	return OK;
}

status_t print_vector_xml(const ADT_Vector_t * vector, FILE * fo)
{
	size_t i;

	print_header_xml(fo);

	for(i=0; i < vector -> alloc_size; i++)
		print_track_xml(vector-> elements[i], fo);
	
	print_footer_xml(fo);

	return OK;
}

status_t print_vector_csv(const ADT_Vector_t * vector, FILE * fo)
{
	size_t i;

	for(i=0; i < vector -> alloc_size; i++)
		print_track_csv(vector-> elements[i], fo);

	return OK;
}


status_t print_track_csv(ADT_Track_t * track, FILE * fo)
{
	if(track == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf (fo,"%s%c%s%c%hu%c%s\n", track -> name, CSV_DELIMITER, track -> artist,
		CSV_DELIMITER, track -> year, CSV_DELIMITER , genres [track-> genre]);

	return OK;
}
