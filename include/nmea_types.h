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

struct ZDA {
	float utc_time;

	uint16_t year;
	int8_t hour_gmt_offset;
	uint8_t min_gmt_offset;
	uint8_t day; // from 01 to 31
	uint8_t month; // from 01 to 12
};

#endif // TYPES_H
