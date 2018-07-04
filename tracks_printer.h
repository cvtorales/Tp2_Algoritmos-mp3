# ifndef TRACKS_PRINTER__H
# define TRACKS_PRINTER__H

# include <stdio.h>
# include "errors.h"
# include "types.h"
# include "vector.h"
# include "track.h"

typedef status_t (* print_header_t)(FILE * fo);
typedef status_t (* print_track_t)(const ADT_Track_t * track, FILE * fo);
typedef status_t (* print_footer_t)(FILE * fo);

status_t export_track_vector(const ADT_Vector_t * vector, track_list_format_t format, FILE * fo);

status_t print_header_xml(FILE * fo);
status_t print_track_xml(const ADT_Track_t * track, FILE * fo);
status_t print_footer_xml(FILE * fo);

status_t print_header_csv(FILE * fo);
status_t print_track_csv(const ADT_Track_t * track, FILE * fo);
status_t print_footer_csv(FILE * fo);

# endif