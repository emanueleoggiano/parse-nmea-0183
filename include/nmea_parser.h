#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include <stddef.h> // used for size_t
#include "nmea_errors.h"
#include "nmea_types.h"

/******************* CHECK SUM *******************/

// Valide the given checksum using XOR
enum NmeaErrCodes validate_checksum(const char *s);

/******************* UTILITIES *******************/

// Find the index relative to the first field
enum NmeaErrCodes skip_msg_id(const char *s, size_t *index);

#endif // NMEA_PARSER_H
