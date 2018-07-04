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


print_header_t print_header[NUMBER_OF_PRINTERS_FUNCTIONS] =
{
	print_header_csv,
	print_header_xml
};

print_track_t print_track[NUMBER_OF_PRINTERS_FUNCTIONS] =
{
	print_track_csv,
	print_track_xml
};

print_footer_t print_footer[NUMBER_OF_PRINTERS_FUNCTIONS] =
{
	print_footer_csv,
	print_footer_xml
};

status_t export_track_vector(const ADT_Vector_t * vector, track_list_format_t format, FILE * fo)
{
	size_t i;

	if (fo == NULL || vector == NULL )
		return ERROR_NULL_POINTER;

	(*(print_header[format]))(fo);
	
	for(i=0; i < vector -> alloc_size; i++)
		(*(print_track[format]))(vector -> elements[i], fo);

	(*(print_footer[format]))(fo);
	
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

status_t print_track_xml(const ADT_Track_t * track, FILE * fo)
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

status_t print_track_csv(const ADT_Track_t * track, FILE * fo)
{
	if(track == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf (fo,"%s%c%s%c%hu%c%s\n", track -> name, CSV_DELIMITER, track -> artist,
		CSV_DELIMITER, track -> year, CSV_DELIMITER , genres [track-> genre]);

	return OK;
}

status_t print_header_csv(FILE * fo)
{
	if(fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf (fo,"%s%c%s%c%s%c%s\n", CSV_HEADER_NAME, CSV_DELIMITER, CSV_HEADER_ARTIST,
		CSV_DELIMITER, CSV_HEADER_YEAR, CSV_DELIMITER , CSV_HEADER_GENRES);

	return OK;
}

status_t print_footer_csv(FILE * fo)
{
	if(fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo, "%s\n", CSV_CLOSE_TRACKS_TAG );

	return OK;
}
