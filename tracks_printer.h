# ifndef TRACKS_PRINTER__H
# define TRACKS_PRINTER__H

# include <stdio.h>
# include "errors.h"
#include "types.h"

typedef status_t (* printer_t)(const ADT_Vector_t * vector, FILE * fo);

status_t export_track_vector(const ADT_Vector_t * vector, track_list_format_t format, FILE * fo);
status_t print_header_xml(FILE * fo);
status_t print_track_xml(ADT_Track_t * track, FILE * fo);
status_t print_track_csv(ADT_Track_t * track, FILE * fo);
status_t print_footer_xml(FILE * fo);
status_t print_vector_xml(const ADT_Vector_t * vector, FILE * fo);
status_t print_vector_csv(const ADT_Vector_t * vector, FILE * fo);

# endif