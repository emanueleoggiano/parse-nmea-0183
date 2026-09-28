#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include "nmea_errors.h"
#include "nmea_types.h"

/******************* CHECK SUM *******************/
enum NmeaErrCodes validate_checksum(const char *s);

#endif // NMEA_PARSER_H
