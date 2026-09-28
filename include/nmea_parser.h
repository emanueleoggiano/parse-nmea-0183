#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include "nmea_errors.h"
#include "nmea_types.h"

/******************* CHECK SUM *******************/
enum NmeaErrCodes validate_checksum(const char *s);



/******************* GGA *******************/
enum NmeaErrCodes initialize_gga(struct GGA *gga_msg);
enum NmeaErrCodes parse_gga(const char *s, struct GGA *gga_msg);

#endif // NMEA_PARSER_H
