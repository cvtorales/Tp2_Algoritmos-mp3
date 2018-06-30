# include <stdio.h>
# include <string.h>
# include "errors.h"

static char * errors [MAX_ERRORS] =
{
	MSG_OK,
	MSG_ERROR_NULL_POINTER,
	MSG_ERROR_NO_MEMORY,
	MSG_ERROR_INPUT_MP3_FILE,
	MSG_ERROR_OUTPUT_FILE,
	MSG_ERROR_DISK_SPACE,
	MSG_ERROR_CORRUPTED_FILE,
	MSG_ERROR_PROG_INVOCATION,
	MSG_ERROR_OCUPPIED_MEMORY
};

status_t print_error_msg (status_t st) 
{
	fprintf (stderr, "%s\n", errors [st]);
	
	return OK;
}
