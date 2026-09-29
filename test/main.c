#include <stdio.h>

#include "nmea_errors.h"
#include "nmea_parser.h"
#include "nmea_types.h"
#include "nmea_protocols.h"

int main(void)
{
    const char *nmea_string = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";

    enum NmeaErrCodes status;
    struct GGA msg;

    status = initialize_gga(&msg);

    if (status != NMEA_OK) {
        fprintf(stderr, "ERROR: failed initialization!");
        return -1;
    }

    
    status = parse_gga(&msg, nmea_string);

    if (status == NMEA_OK) {
        fprintf(stdout, "The given string is: %s\n", nmea_string);
        fprintf(stdout, "Latitude: %.4f %c\n", msg.latitude, msg.lat_dir);
    } else {
        fprintf(stdout, "ERROR code %d\n", status);
    }



    return 0;
}
