# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "errors.h"
# include "mp3.h"
# include "types.h"
# include "track.h"
# include "setup.h"

/*Crea un ADT_Track (tipo de dato abstracto), atraves de un archivo .mp3
 y lo almacena en una variable estatica.*/

status_t ADT_Track_new_from_file (void * pvoid, FILE * file_mp3)
{
    size_t length;
    char * temp;
    char header[MP3_HEADER_SIZE];
    char buf[MP3_HEADER_SIZE];
    ADT_Track_t * ptrack;

    if (file_mp3 == NULL || pvoid == NULL)
       return ERROR_NULL_POINTER;

  	ptrack = (ADT_Track_t *) pvoid;	
    
    fseek(file_mp3, 0, SEEK_END);                       	/*manda el puntero al final del archivo*/
    length = ftell(file_mp3);                               /*da la distancia al comienzo*/
    fseek(file_mp3, length - MP3_HEADER_SIZE, SEEK_SET);   	/*se para en el header MP3*/

    fread(header,sizeof(char), MP3_HEADER_SIZE, file_mp3);

    memcpy(buf, header + LEXEM_START_TITLE, LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    strcpy (ptrack -> name, buf);

    memcpy(buf,header + LEXEM_START_ARTIST, LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    strcpy (ptrack -> artist, buf);

    memcpy(buf, header + LEXEM_START_YEAR, LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    ptrack -> year = strtol (buf, &temp, 10);

    if (*temp)
    	return ERROR_CORRUPTED_FILE;

    memcpy(buf, header + LEXEM_START_GENRE, LEXEM_SPAN_GENRE);
    ptrack -> genre = buf [0];

    return OK;
}

/*Destruye un ADT_Track (tipo de dato abstracto), libera la memoria pedida y pone
sus campos a un valor seguro.*/

status_t ADT_Track_destroy (void * pvoid)
{
	ADT_Track_t * ptrack;

	if (pvoid == NULL)
		return ERROR_NULL_POINTER;

	ptrack = (ADT_Track_t *) pvoid;

	strcpy (ptrack -> name, DEFAULT_TRACK_NAME);
	strcpy (ptrack -> artist, DEFAULT_TRACK_ARTIST);

	ptrack -> year = DEFAULT_TRACK_YEAR;
	ptrack -> genre = Other;

	free (ptrack);
	ptrack = NULL;

	return OK;
}

/*Clona un ADT_Track (tipo de dato abstracto), pide memoria y copia los campos de otro
ADT_Track (este puede ser estatico o no).*/

status_t ADT_Track_clone (const void * pvoid1, void ** pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t ** ptrack2;

	if (pvoid1 == NULL)                      /*pvoid2 puede ser NULL.*/
		return ERROR_NULL_POINTER;

	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t **) pvoid2;

	if ((*ptrack2 = (ADT_Track_t *) malloc (sizeof (ADT_Track_t))) == NULL)
    	return ERROR_NO_MEMORY;

	strcpy ( (*ptrack2) -> name, ptrack1 -> name);
	strcpy ( (*ptrack2) -> artist, ptrack1 -> artist);

	(*ptrack2) -> year = ptrack1 -> year;
	(*ptrack2) -> genre = ptrack1 -> genre;

	return OK;
}


/*Compara 2 ADT_Track (tipo de dato abstracto) por campo nombre*/

int ADT_Track_compare_by_name (const void * pvoid1, const void * pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t * ptrack2;

	if (pvoid1 == NULL || pvoid2 == NULL)
		return ERROR_NULL_POINTER;

	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t *) pvoid2;

	return strcmp (ptrack1 -> name, ptrack2 -> name);
}

/*Compara 2 ADT_Track (tipo de dato abstracto) por campo Artista*/

int ADT_Track_compare_by_artist (const void * pvoid1, const void * pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t * ptrack2;

	if (pvoid1 == NULL || pvoid2 == NULL)
		return ERROR_NULL_POINTER;

	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t *) pvoid2;

	return strcmp (ptrack1 -> artist, ptrack2 -> artist);
}

/*Compara 2 ADT_Track (tipo de dato abstracto) por campo genero*/

int ADT_Track_compare_by_genre (const void * pvoid1, const void * pvoid2)
{
	ADT_Track_t * ptrack1;
	ADT_Track_t * ptrack2;

	if (pvoid1 == NULL || pvoid2 == NULL)
		return ERROR_NULL_POINTER;

	ptrack1 = (ADT_Track_t *) pvoid1;
	ptrack2 = (ADT_Track_t *) pvoid2;

	return ptrack1 -> genre - ptrack2 -> genre;
}


/*Exporta un ADT_Track (tipo de dato abstracto) con formato csv en un flujo fo, requiere un 
contexto de impresion.*/

status_t ADT_Track_export_as_csv (const void * pvoid, const void * pcontext, FILE * fo)
{
	ADT_Track_t * ptrack;
	context_t * context;

	static string genres [NUMBER_OF_GENRES] =
	{
		GENRE_BLUES,
		GENRE_CLASSIC_ROCK,
		GENRE_COUNTRY,
		GENRE_DANCE,
		GENRE_DISCO,
		GENRE_FUNK,
		GENRE_GRUNGE,
		GENRE_HIP_HOP,
		GENRE_JAZZ,
		GENRE_METAL,
		GENRE_NEW_AGE,
		GENRE_OLDIES,
		GENRE_OTHER, 
		GENRE_POP, 
		GENRE_R_AND_B,
		GENRE_RAP,
		GENRE_REGGAE,
		GENRE_ROCK,
		GENRE_TECHNO,
		GENRE_INDUSTRIAL,
		GENRE_ALTERNATIVE,
		GENRE_SKA,
		GENRE_DEATH_METAL,
		GENRE_PRANKS,
		GENRE_SOUNDTRACK,
		GENRE_EURO_TECHNO,
		GENRE_AMBIENT,
		GENRE_TRIP_HOP, 
		GENRE_VOCAL,
		GENRE_JAZZ_PLUS_FUNK,
		GENRE_FUSION,
		GENRE_TRANCE,
		GENRE_CLASSICAL,
		GENRE_INSTRUMENTAL,
		GENRE_ACID,
		GENRE_HOUSE,
		GENRE_GAME,
		GENRE_SOUND_CLIP,
		GENRE_GOSPEL,
		GENRE_NOISE,
		GENRE_ALTERNROCK,
		GENRE_BASS,
 		GENRE_SOUL,
		GENRE_PUNK,
 		GENRE_SPACE,
 		GENRE_MEDITATIVE, 
 		GENRE_INSTRUMENTAL_POP,
 		GENRE_INSTRUMENTAL_ROCK, 
 		GENRE_ETHNIC,
 		GENRE_GOTHIC,
		GENRE_DARKWAVE, 
 		GENRE_TECHNO_INDUSTRIAL,
 		GENRE_ELECTRONIC,
		GENRE_POP_FOLK,
		GENRE_EURODANCE,
 		GENRE_DREAM, 
 		GENRE_SOUTHERN_ROCK,
 		GENRE_COMEDY,
		GENRE_CULT,
 		GENRE_GANGSTA, 
	 	GENRE_TOP_40,
 		GENRE_CHRISTIAN_RAP,
		GENRE_POP_FUNK,
		GENRE_JUNGLE,
		GENRE_NATIVE_AMERICAN, 
 		GENRE_CABARET,
 		GENRE_NEW_WAVE,
 		GENRE_PSYCHADELIC,
 		GENRE_RAVE,
 		GENRE_SHOWTUNES,
 		GENRE_TRAILER, 
 		GENRE_Lo_Fi,
		GENRE_TRIBAL,
 		GENRE_ACID_PUNK,
 		GENRE_ACID_JAZZ,
 		GENRE_POLKA,
		GENRE_RETRO,
		GENRE_MUSICAL,
		GENRE_ROCK_AND_ROLL,
		GENRE_HARD_ROCK,
		GENRE_FOLK,
		GENRE_FOLK_ROCK,
		GENRE_NATIONAL_FOLK,
		GENRE_SWING,
		GENRE_FAST_FUSION,
		GENRE_BEBOB,
		GENRE_LATIN,
		GENRE_REVIVAL,
		GENRE_CELTIC,
		GENRE_BLUEGRASS,
		GENRE_AVANTGARDE,
		GENRE_GOTHIC_ROCK,
		GENRE_PROGRESSIVE_ROCK,
		GENRE_PSYCHEDELIC_ROCK,
		GENRE_SYMPHONIC_ROCK,
		GENRE_SLOW_ROCK,
		GENRE_BIG_BAND,
		GENRE_CHORUS,
		GENRE_EASY_LISTENING,
		GENRE_ACOUSTIC,
		GENRE_HUMOUR,
		GENRE_SPEECH,
		GENRE_CHANSON,
		GENRE_OPERA,
		GENRE_CHAMBER_MUSIC,
		GENRE_SONATA,
		GENRE_SYMPHONY,
 		GENRE_BOOTY_BRASS,
		GENRE_PRIMUS,
 		GENRE_PORN_GROOVE,
		GENRE_SATIRE,
		GENRE_SLOW_JAM,
		GENRE_CLUB,
		GENRE_TANGO,
		GENRE_SAMBA,
		GENRE_FOLKLORE,
		GENRE_BALLAD,
		GENRE_POWEER_BALLLAD,
		GENRE_RHYTMIC_SOUL,
		GENRE_FREESTYLE,
		GENRE_DUET,
		GENRE_PUNK_ROCK,
		GENRE_DRUM_SOLO,
		GENRE_A_CAPELA,
		GENRE_EURO_HOUSE,
 		GENRE_DANCE_HALL,	
	};

	if (pvoid == NULL || pcontext == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	ptrack = (ADT_Track_t *) pvoid;
	context = (context_t *) pcontext;

	fprintf (fo,"%s%c%s%c%hu%c%s\n", ptrack -> name, context -> csv_delimiter, ptrack -> artist,
		context -> csv_delimiter, ptrack -> year, context -> csv_delimiter , genres [ptrack-> genre]);

	return OK;
}

/*Exporta un ADT_Track (tipo de dato abstracto) con formato xml en un flujo fo, requiere un 
contexto de impresion.*/

status_t ADT_Track_export_as_xml (const void * pvoid, const void * pcontext, FILE * fo)
{
	size_t i;
	ADT_Track_t * ptrack;
	context_t * context;

	static string genres [NUMBER_OF_GENRES] =
	{
		GENRE_BLUES,
		GENRE_CLASSIC_ROCK,
		GENRE_COUNTRY,
		GENRE_DANCE,
		GENRE_DISCO,
		GENRE_FUNK,
		GENRE_GRUNGE,
		GENRE_HIP_HOP,
		GENRE_JAZZ,
		GENRE_METAL,
		GENRE_NEW_AGE,
		GENRE_OLDIES,
		GENRE_OTHER, 
		GENRE_POP, 
		GENRE_R_AND_B,
		GENRE_RAP,
		GENRE_REGGAE,
		GENRE_ROCK,
		GENRE_TECHNO,
		GENRE_INDUSTRIAL,
		GENRE_ALTERNATIVE,
		GENRE_SKA,
		GENRE_DEATH_METAL,
		GENRE_PRANKS,
		GENRE_SOUNDTRACK,
		GENRE_EURO_TECHNO,
		GENRE_AMBIENT,
		GENRE_TRIP_HOP, 
		GENRE_VOCAL,
		GENRE_JAZZ_PLUS_FUNK,
		GENRE_FUSION,
		GENRE_TRANCE,
		GENRE_CLASSICAL,
		GENRE_INSTRUMENTAL,
		GENRE_ACID,
		GENRE_HOUSE,
		GENRE_GAME,
		GENRE_SOUND_CLIP,
		GENRE_GOSPEL,
		GENRE_NOISE,
		GENRE_ALTERNROCK,
		GENRE_BASS,
 		GENRE_SOUL,
		GENRE_PUNK,
 		GENRE_SPACE,
 		GENRE_MEDITATIVE, 
 		GENRE_INSTRUMENTAL_POP,
 		GENRE_INSTRUMENTAL_ROCK, 
 		GENRE_ETHNIC,
 		GENRE_GOTHIC,
		GENRE_DARKWAVE, 
 		GENRE_TECHNO_INDUSTRIAL,
 		GENRE_ELECTRONIC,
		GENRE_POP_FOLK,
		GENRE_EURODANCE,
 		GENRE_DREAM, 
 		GENRE_SOUTHERN_ROCK,
 		GENRE_COMEDY,
		GENRE_CULT,
 		GENRE_GANGSTA, 
	 	GENRE_TOP_40,
 		GENRE_CHRISTIAN_RAP,
		GENRE_POP_FUNK,
		GENRE_JUNGLE,
		GENRE_NATIVE_AMERICAN, 
 		GENRE_CABARET,
 		GENRE_NEW_WAVE,
 		GENRE_PSYCHADELIC,
 		GENRE_RAVE,
 		GENRE_SHOWTUNES,
 		GENRE_TRAILER, 
 		GENRE_Lo_Fi,
		GENRE_TRIBAL,
 		GENRE_ACID_PUNK,
 		GENRE_ACID_JAZZ,
 		GENRE_POLKA,
		GENRE_RETRO,
		GENRE_MUSICAL,
		GENRE_ROCK_AND_ROLL,
		GENRE_HARD_ROCK,
		GENRE_FOLK,
		GENRE_FOLK_ROCK,
		GENRE_NATIONAL_FOLK,
		GENRE_SWING,
		GENRE_FAST_FUSION,
		GENRE_BEBOB,
		GENRE_LATIN,
		GENRE_REVIVAL,
		GENRE_CELTIC,
		GENRE_BLUEGRASS,
		GENRE_AVANTGARDE,
		GENRE_GOTHIC_ROCK,
		GENRE_PROGRESSIVE_ROCK,
		GENRE_PSYCHEDELIC_ROCK,
		GENRE_SYMPHONIC_ROCK,
		GENRE_SLOW_ROCK,
		GENRE_BIG_BAND,
		GENRE_CHORUS,
		GENRE_EASY_LISTENING,
		GENRE_ACOUSTIC,
		GENRE_HUMOUR,
		GENRE_SPEECH,
		GENRE_CHANSON,
		GENRE_OPERA,
		GENRE_CHAMBER_MUSIC,
		GENRE_SONATA,
		GENRE_SYMPHONY,
 		GENRE_BOOTY_BRASS,
		GENRE_PRIMUS,
 		GENRE_PORN_GROOVE,
		GENRE_SATIRE,
		GENRE_SLOW_JAM,
		GENRE_CLUB,
		GENRE_TANGO,
		GENRE_SAMBA,
		GENRE_FOLKLORE,
		GENRE_BALLAD,
		GENRE_POWEER_BALLLAD,
		GENRE_RHYTMIC_SOUL,
		GENRE_FREESTYLE,
		GENRE_DUET,
		GENRE_PUNK_ROCK,
		GENRE_DRUM_SOLO,
		GENRE_A_CAPELA,
		GENRE_EURO_HOUSE,
 		GENRE_DANCE_HALL,	
	};
	
	if (pvoid == NULL || pcontext == NULL || fo == NULL)
		return ERROR_NULL_POINTER;
	
	ptrack = (ADT_Track_t *) pvoid;
	context = (context_t *) pcontext;
	
	if (context -> xml_index == 0)
	{
		for (i = 0; i < 2; ++i)
			fprintf (fo, "%s\n" ,context -> xml_tags [i]);
	}

	context -> xml_index ++;
	i = 2;

	fprintf (fo, "\t%s\n" ,context -> xml_tags [i]);
	i ++ ;

	fprintf (fo, "\t\t%s %s %s\n" ,context -> xml_tags [i], ptrack -> name,  context -> xml_tags [i + 1]);
	i += 2;

	fprintf (fo, "\t\t%s %s %s\n" ,context -> xml_tags [i], ptrack -> artist,  context -> xml_tags [i + 1]);
	i += 2;

	fprintf (fo, "\t\t%s %hu %s\n" ,context -> xml_tags [i], ptrack -> year,  context -> xml_tags [i + 1]);
	i += 2;

	fprintf (fo, "\t\t%s %s %s\n" ,context -> xml_tags [i], genres [ptrack -> genre] ,  context -> xml_tags [i + 1]);
	i += 2;

	fprintf (fo, "%s\n" , context -> xml_tags [i]);
	i ++;
	
	if (context -> xml_index == context -> xml_close_mark)
		fprintf (fo, "%s\n" , context -> xml_tags [i]);
	
	return OK;
}


