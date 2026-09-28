#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

struct GGA {
    double latitude;
    double longitude;

    float utc_time;
    float hdop;
    float altitude;
    float geoid_sep;
    float dgps_age;

    uint16_t station_id;
    uint8_t quality;
    uint8_t satellites;

    char lat_dir; // latitude direction (N/S)
    char lon_dir; // longitude direction (E/W)
    char alt_uom; // unit of measure for altitude (the standard is M)
    char geoid_uom; // unit of measure for geoid separation (the standard is M)
};

#endif // TYPES_H
