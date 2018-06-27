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
	Blues = 0,
	Classic_Rock = 1,
	Country = 2,
	Dance = 3,
	Disco = 4,
	Funk = 5,
	Grunge = 6,
	Hip_Hop = 7,
	Jazz = 8,
	Metal = 9,
	New_Age = 10,
	Oldies = 11,
	Other = 12,
	Pop = 13,
	R_and_B = 14,
	Rap = 15,
	Reggae = 16,
	Rock = 17,
	Techno = 18,
	Industrial = 19,
	Alternative = 20,
	Ska = 21,
	Death_Metal = 22,
	Pranks = 23,
	Soundtrack = 24,
	Euro_Techno = 25,
	Ambient = 26,
	Trip_Hop = 27,
	Vocal = 28,
	Jazz_plus_Funk = 29,
	Fusion = 30,
	Trance = 31,
	Classical = 32,
	Instrumental = 33,
	Acid = 34,
	House = 35,
	Game = 36,
	Sound_Clip = 37,
	Gospel = 38,
	Noise = 39,
	AlternRock = 40,
	Bass = 41,
	Soul = 42,
	Punk = 43,
	Space = 44,
	Meditative = 45,
	Instrumental_Pop = 46,
	Instrumental_Rock = 47,
	Ethnic = 48,
	Gothic = 49,
	Darkwave = 50,
	Techno_Industrial = 51,
	Electronic = 52,
	Pop_Folk = 53,
	Eurodance = 54,
	Dream = 55,
	Southern_Rock = 56,
	Comedy = 57,
	Cult = 58,
	Gangsta = 59,
	Top_40 = 60,
	Christian_Rap = 61,
	Pop_Funk = 62,
	Jungle = 63,
	Native_American = 64,
	Cabaret = 65,
	New_Wave = 66,
	Psychadelic = 67,
	Rave = 68,
	Showtunes = 69,
	Trailer = 70,
	Lo_Fi = 71,
	Tribal = 72,
	Acid_Punk = 73,
	Acid_Jazz = 74,
	Polka = 75,
	Retro = 76,
	Musical = 77,
	Rock_and_Roll = 78,
	Hard_Rock = 79,
	Folk = 80,
	Folk_Rock = 81,
	National_Folk = 82,
	Swing = 83,
	Fast_Fusion = 84,
	Bebob = 85,
	Latin = 86,
	Revival = 87,
	Celtic = 88,
	Bluegrass = 89,
	Avantgarde = 90,
	Gothic_Rock = 91,
	Progressive_Rock = 92,
	Psychedelic_Rock = 93,
	Symphonic_Rock = 94,
	Slow_Rock = 95,
	Big_Band = 96,
	Chorus = 97,
	Easy_Listening = 98,
	Acoustic = 99,
	Humour = 100,
	Speech = 101,
	Chanson = 102,
	Opera = 103,
	Chamber_Music = 104,
	Sonata = 105,
	Symphony = 106,
	Booty_Brass = 107,
	Primus = 108,
	Porn_Groove = 109,
	Satire = 110,
	Slow_Jam = 111,
	Club = 112,
	Tango = 113,
	Samba = 114,
	Folklore = 115,
	Ballad = 116,
	Poweer_Ballad = 117,
	Rhytmic_Soul = 118,
	Freestyle = 119,
	Duet = 120,
	Punk_Rock = 121,
	Drum_Solo = 122,
	A_Capela = 123,
	Euro_House = 124,
	Dance_Hall = 125		
} track_genre_t;

status_t get_mp3_header (FILE * file_mp3, ADT_Vector_t ** ADT_Vector);

# endif
