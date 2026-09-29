#include "nmea_parser.h"
#include "nmea_errors.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/*************************** CHECKSUM ***************************/

/* Compute the checksum of a given NMEA0183 string.   */
/* Check whether the calculated checksum is equal to  */
/* the given checksum in the NMEA0183 string          */
enum NmeaErrCodes validate_checksum(const char *s)
{
    if (s == NULL) {
        return NMEA_ERR_INVALID_ARGUMENT;
    }

    if (s[0] != '$') {
        return NMEA_ERR_BAD_STRING;
    }

    uint8_t checksum = 0;
    
    size_t i = 1;
    for (; s[i] != '*' && s[i] != 0; i++) {
        checksum ^= (uint8_t)s[i];
    }

    // Validation of the checksum
    if (s[i] == '*' && strlen(&s[i]) >= 3) {

        char given_checksum_str[3] = {s[i+1], s[i+2], '\0'};

        uint8_t given_checksum = (uint8_t)strtol(given_checksum_str, NULL, 16);

        if (checksum == given_checksum) {
            return NMEA_OK;
        }
    }

    return NMEA_ERR_BAD_CHECKSUM;
}


/*************************** UTILITIES ***************************/

/* Find the position of the first field in a NMEA-0183 string */
enum NmeaErrCodes skip_msg_id(const char *s, size_t *index)
{
	if (s == NULL || index == NULL) {
		return NMEA_ERR_INVALID_ARGUMENT;
	}

	char *first_comma = strchr(s, ',');

	if (first_comma == NULL) {
		return NMEA_ERR_BAD_STRING;
	}

	*index = (size_t)(first_comma - s + 1);

	return NMEA_OK;
}
