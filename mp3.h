# ifndef MP3__H
# define MP3__H
# include <stdio.h>
# include "errors.h"
# include "vector.h"

# define MP3_HEADER_SIZE		128
# define LEXEM_START_TAG     0
# define LEXEM_SPAN_TAG      3
# define LEXEM_START_TITLE   3
# define LEXEM_SPAN_TITLE   30
# define LEXEM_START_ARTIST 33
# define LEXEM_SPAN_ARTIST  30
# define LEXEM_START_ALBUM  63
# define LEXEM_SPAN_ALBUM   30
# define LEXEM_START_YEAR   93
# define LEXEM_SPAN_YEAR     4
# define LEXEM_START_COMMENT 97
# define LEXEM_SPAN_COMMENT  30
# define LEXEM_START_GENRE  127
# define LEXEM_SPAN_GENRE     1
# define NUMBER_OF_GENRES	126
# define GENRE_BLUES "Blues"
# define GENRE_CLASSIC_ROCK "Classic Rock"
# define GENRE_COUNTRY "Country"
# define GENRE_DANCE "Dance"
# define GENRE_DISCO "Disco"
# define GENRE_FUNK "Funk"
# define GENRE_GRUNGE "Grunge"
# define GENRE_HIP_HOP "Hip Hop"
# define GENRE_JAZZ "Jazz"
# define GENRE_METAL "Metal"
# define GENRE_NEW_AGE "New Age"
# define GENRE_OLDIES "oldies"
# define GENRE_OTHER "OTHER"
# define GENRE_POP "Pop"
# define GENRE_R_AND_B "R&B"
# define GENRE_RAP "Rap"
# define GENRE_REGGAE "Reggae"
# define GENRE_ROCK "Rock"
# define GENRE_TECHNO "Techno"
# define GENRE_INDUSTRIAL "Industrial"
# define GENRE_ALTERNATIVE "Alternative"
# define GENRE_SKA "Ska"
# define GENRE_DEATH_METAL "Death Metal"
# define GENRE_PRANKS "Pranks"
# define GENRE_SOUNDTRACK "Soundtrack"
# define GENRE_EURO_TECHNO "Euro Techno"
# define GENRE_AMBIENT "Ambient"
# define GENRE_TRIP_HOP "Trip Hop"
# define GENRE_VOCAL "Vocal"
# define GENRE_JAZZ_PLUS_FUNK "Jazz + Funk"
# define GENRE_FUSION "Fusion"
# define GENRE_TRANCE "Trance"
# define GENRE_CLASSICAL "Classical"
# define GENRE_INSTRUMENTAL "Instrumental"
# define GENRE_ACID "Acid"
# define GENRE_HOUSE "House"
# define GENRE_GAME "Game"
# define GENRE_SOUND_CLIP "Sound Clip"
# define GENRE_GOSPEL "Gospel"
# define GENRE_NOISE "Noise"
# define GENRE_ALTERNROCK "AlternRock"
# define GENRE_BASS "Bass"
# define GENRE_SOUL "Soul"
# define GENRE_PUNK "Punk"
# define GENRE_SPACE "Space"
# define GENRE_MEDITATIVE "Meditative"
# define GENRE_INSTRUMENTAL_POP "Instrumental Pop"
# define GENRE_INSTRUMENTAL_ROCK "Instrumental Rock"
# define GENRE_ETHNIC "Ethnic"
# define GENRE_GOTHIC "Gothic"
# define GENRE_DARKWAVE "Darkwave"
# define GENRE_TECHNO_INDUSTRIAL "Techno Industrial"
# define GENRE_ELECTRONIC "Electronic"
# define GENRE_POP_FOLK "Pop Folk"
# define GENRE_EURODANCE "Eurodance"
# define GENRE_DREAM "Dream"
# define GENRE_SOUTHERN_ROCK "Southern Rock"
# define GENRE_COMEDY "Comedy"
# define GENRE_CULT "Cult"
# define GENRE_GANGSTA "Gangsta"
# define GENRE_TOP_40 "Top 40"
# define GENRE_CHRISTIAN_RAP "Christian Rap"
# define GENRE_POP_FUNK "Pop Funk"
# define GENRE_JUNGLE "Jungle"
# define GENRE_NATIVE_AMERICAN "Native American"
# define GENRE_CABARET "Cabaret"
# define GENRE_NEW_WAVE "New Wake"
# define GENRE_PSYCHADELIC "Psychadelic"
# define GENRE_RAVE "Rave"
# define GENRE_SHOWTUNES "Showtunes"
# define GENRE_TRAILER "Trailer"
# define GENRE_Lo_Fi "Lo-Fi"
# define GENRE_TRIBAL "Tribal"
# define GENRE_ACID_PUNK "Acid Punk"
# define GENRE_ACID_JAZZ "Acid Jazz"
# define GENRE_POLKA "Polka"
# define GENRE_RETRO "Retro"
# define GENRE_MUSICAL "Musical"
# define GENRE_ROCK_AND_ROLL "Rock&Roll"
# define GENRE_HARD_ROCK "Hard Rock"
# define GENRE_FOLK "Folk"
# define GENRE_FOLK_ROCK "Folk Rock"
# define GENRE_NATIONAL_FOLK "National Folk"
# define GENRE_SWING "Swing"
# define GENRE_FAST_FUSION "Fast Fusion"
# define GENRE_BEBOB "Bebob"
# define GENRE_LATIN "Latin"
# define GENRE_REVIVAL "Revival"
# define GENRE_CELTIC "Celtic"
# define GENRE_BLUEGRASS "Bluegrass"
# define GENRE_AVANTGARDE "Avantgarde"
# define GENRE_GOTHIC_ROCK "Gothic Rock"
# define GENRE_PROGRESSIVE_ROCK "Progressive Rock"
# define GENRE_PSYCHEDELIC_ROCK "Psychedelic Rock"
# define GENRE_SYMPHONIC_ROCK "Symphonic Rock"
# define GENRE_SLOW_ROCK "Slow Rock"
# define GENRE_BIG_BAND "Big Band"
# define GENRE_CHORUS "Chorus"
# define GENRE_EASY_LISTENING "Easy Listening"
# define GENRE_ACOUSTIC "Acoustic"
# define GENRE_HUMOUR "Humour"
# define GENRE_SPEECH "Speech"
# define GENRE_CHANSON "Chanson"
# define GENRE_OPERA "Opera"
# define GENRE_CHAMBER_MUSIC "Chamber Music"
# define GENRE_SONATA "Sonata"
# define GENRE_SYMPHONY "Symphony"
# define GENRE_BOOTY_BRASS "Booty Brass"
# define GENRE_PRIMUS "Primus"
# define GENRE_PORN_GROOVE "Porn Groove"
# define GENRE_SATIRE "Satire"
# define GENRE_SLOW_JAM "Slow Jam"
# define GENRE_CLUB "Club"
# define GENRE_TANGO "Tango"
# define GENRE_SAMBA "Samba"
# define GENRE_FOLKLORE "Folklore"
# define GENRE_BALLAD "Ballad"
# define GENRE_POWEER_BALLLAD "Poweer Ballad"
# define GENRE_RHYTMIC_SOUL "Rhytmic Soul"
# define GENRE_FREESTYLE "Freestyle"
# define GENRE_DUET "Duet"
# define GENRE_PUNK_ROCK "Punk Rock"
# define GENRE_DRUM_SOLO "Drum Solo"
# define GENRE_A_CAPELA "A Capela"
# define GENRE_EURO_HOUSE "Euro_House"
# define GENRE_DANCE_HALL "Dance_Hall"	

typedef enum
{
		BLUES = 0,
		CLASSIC_ROCK = 1,
		COUNTRY = 2,
		DANCE = 3,
		DISCO = 4,
		FUNK = 5,
		GRUNGE = 6,
		HIP_HOP = 7,
		JAZZ = 8,
		METAL = 9,
		NEW_AGE = 10, 
		OLDIES = 11, 
		OTHER = 12, 
		POP =  13,
		R_AND_B = 14,
		RAP = 15,
		REGGAE = 16, 
		ROCK =  17,
		TECHNO = 18,
		INDUSTRIAL = 19,
		ALTERNATIVE = 20,
		SKA = 21,
		DEATH_METAL = 22, 
		PRANKS = 23,
		SOUNDTRACK = 24,
		EURO_TECHNO = 25, 
		AMBIENT = 26,
		TRIP_HOP = 27,
		VOCAL = 28,
		JAZZ_PLUS_FUNK = 29, 
		FUSION = 30,
		TRANCE = 31,
		CLASSICAL = 32,
		INSTRUMENTAL = 33,
		ACID = 34,
		HOUSE = 35, 
		GAME = 36,
		SOUND_CLIP = 37, 
		GOSPEL = 38, 
		NOISE = 39,
		ALTERNROCK = 40, 
		BASS = 41,
		SOUL = 42, 
		PUNK = 43,
		SPACE = 44,
		MEDITATIVE = 45,
		INSTRUMENTAL_POP = 46,
		INSTRUMENTAL_ROCK = 47, 
		ETHNIC = 48,
		GOTHIC = 49,
		DARKWAVE = 50,
		TECHNO_INDUSTRIAL = 51, 
		ELECTRONIC = 52,
		POP_FOLK = 53,
		EURODANCE = 54, 
		DREAM =   55,
		SOUTHERN_ROCK = 56,
		COMEDY =  57,
		CULT = 58,
		GANGSTA = 59, 
		TOP_40 = 60,
		CHRISTIAN_RAP = 61,
		POP_FUNK = 62, 
		JUNGLE = 63,
		NATIVE_AMERICAN = 64, 
		CABARET = 65,
		NEW_WAVE = 66,
		PSYCHADELIC = 67, 
		RAVE = 68,
		SHOWTUNES = 69, 
		TRAILER = 70,
		LO_FI = 71,
		TRIBAL = 72,
		ACID_PUNK = 73,
		ACID_JAZZ = 74, 
		POLKA = 75, 
		RETRO = 76,
		MUSICAL = 77,
		ROCK_AND_ROLL = 78, 
		HARD_ROCK = 79, 
		FOLK =  80,
		FOLK_ROCK = 81,
		NATIONAL_FOLK = 82,
		SWING = 83, 
		FAST_FUSION = 84,
		BEBOB = 85, 
		LATIN = 86,
		REVIVAL = 87, 
		CELTIC = 88,
		BLUEGRASS = 89,
		AVANTGARDE = 90,
		GOTHIC_ROCK = 91,
		PROGRESSIVE_ROCK = 92,
		PSYCHEDELIC_ROCK = 93,
		SYMPHONIC_ROCK = 94, 
		SLOW_ROCK =  95,
		BIG_BAND = 96, 
		CHORUS = 97,
		EASY_LISTENING = 98,  
		ACOUSTIC =  99, 
		HUMOUR  = 100,
		SPEECH = 101,
		CHANSON = 102, 
		OPERA = 103,
		CHAMBER_MUSIC = 104,
		SONATA = 105,
		SYMPHONY = 106,
		BOOTY_BRASS = 107, 
		PRIMUS = 108,
		PORN_GROOVE = 109, 
		SATIRE = 110,
		SLOW_JAM =  111,
		CLUB =  112,
		TANGO = 113,
		SAMBA = 114,
		FOLKLORE =  115,
		BALLAD =  116, 
		POWEER_BALLLAD = 117,
		RHYTMIC_SOUL = 118,
		FREESTYLE = 119, 
		DUET = 120,
		PUNK_ROCK = 121, 
		DRUM_SOLO =  122, 
		A_CAPELA = 123,
		EURO_HOUSE =  124, 
		DANCE_HALL = 125
		
} track_genre_t;


# endif


