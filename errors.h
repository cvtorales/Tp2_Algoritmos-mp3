# ifndef ERRORS__H
# define ERRORS__H

# include <stdio.h>

typedef enum 
{
	OK,
	ERROR_NULL_POINTER,
	ERROR_NO_MEMORY,
	ERROR_INPUT_MP3_FILE,
	ERROR_OUTPUT_FILE,
	ERROR_DISK_SPACE,
	ERROR_CORRUPTED_FILE,
	ERROR_PROG_INVOCATION,
	ERROR_OCUPPIED_MEMORY
} status_t;

# define MAX_ERRORS 9
# define MSG_OK "OK"
# define MSG_ERROR_NULL_POINTER "Puntero nulo"
# define MSG_ERROR_NO_MEMORY "Memoria insuficiente en el sistema"
# define MSG_ERROR_INPUT_MP3_FILE "Archivo .mp3 inválido"
# define MSG_ERROR_OUTPUT_FILE "Archivo de salida inválido"
# define MSG_ERROR_DISK_SPACE "Falta de espacio en disco"
# define MSG_ERROR_CORRUPTED_FILE "Archivo corrupto"
# define MSG_ERROR_PROG_INVOCATION "Los argumentos en linea de orden son inválidos"
# define MSG_ERROR_OCUPPIED_MEMORY "Se intento sobreescribir una posición de memoria ya ocupada"

status_t print_error_msg (status_t st); 

# endif