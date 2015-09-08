#ifndef INC_NMEA_H
#define INC_NMEA_H

#include <stdlib.h>
#include <string.h>

/* nmea sentence max length */
#define NMEA_MAX_LENGTH		50

/* nmea sentence endings */
#define NMEA_END_CHAR_1		'\n'
#define NMEA_END_CHAR_2		'\n'

/* NMEA sentence prefixes */
#define NMEA_PREFIX_LENGTH	5
#define NMEA_PREFIX_GPGLL	"GPGLL"	// Geographic Position, Latitude/Longitude

/* NMEA sentence types */
typedef enum {NMEA_UNKNOWN, NMEA_GPGLL} nmea_t;

typedef struct {
	nmea_t type;
} nmea_s;

typedef struct {
	double minutes;
	int degrees;
	char dir;
} nmea_position;


/* returns number of tokens */
int _nmea_split_sentence(char *sentence, int length, char **values);

/* return gps position longitude or latitude */
int _nmea_get_position(char *s, nmea_position *pos);

/**
 * Get the type of the sentence.
 *
 * sentence needs to be a validated NMEA sentence string.
 */
nmea_t nmea_get_type(const char *sentence);

/**
 * Calculate the checksum of the sentence.
 *
 * sentence needs to be a validated NMEA sentence string.
 */
char nmea_get_checksum(const char *sentence);

/**
 * Check if the sentence has a precalculated checksum.
 *
 * sentence needs to be a validated NMEA sentence string.
 * length is the byte length of the sentence string.
 */
int nmea_has_checksum(const char *sentence, int length);

/**
 * Validate the sentence according to NMEA 0183.
 *
 * - Should start with a dollar sign.
 * - The next five chars should be uppercase letters.
 * - If it has a checksum, it checks it.
 * - Ends with \r\n (<CR><LF>).
 *
 * length is the byte length of the sentence string.
 */
int nmea_validate(const char *sentence, int length);

/**
 * Parses an NMEA sentence string.
 *
 * sentence needs to be a validated NMEA sentence string.
 * length is the byte length of the sentence string.
 */
nmea_s *nmea_parse(char *sentence, int length, nmea_t type);

#endif  /* INC_NMEA_H */