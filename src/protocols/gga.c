#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "nmea_errors.h"
#include "nmea_types.h"
#include "nmea_parser.h"
#include "protocols/gga.h"

#define BUFF_SIZE 20


/* Initialize a GGA MSG. This is necessary before parsing the string */
/*           in case of errors during the parsing operations         */
enum NmeaErrCodes initialize_gga(struct GGA *gga_msg)
{
    if (gga_msg == NULL) {
        return NMEA_ERR_INVALID_ARGUMENT;
    }

    gga_msg->latitude = -9999.0;
    gga_msg->longitude = -9999.0;

    gga_msg->utc_time = -9999.0;
    gga_msg->hdop = -9999.0;
    gga_msg->altitude = -9999.0;
    gga_msg->geoid_sep = -9999.0;
    gga_msg->dgps_age = -9999.0;

    gga_msg->station_id = UINT16_MAX;
    gga_msg->quality = 0;
    gga_msg->satellites = 0;
    gga_msg->lat_dir = '?';
    gga_msg->lon_dir = '?';
    gga_msg->alt_uom = '?';
    gga_msg->geoid_uom = '?';

    return NMEA_OK;
}


enum NmeaErrCodes assign_gga_field(struct GGA *gga_msg, const char *buff, size_t index)
{
    if (gga_msg == NULL || buff == NULL) {
        return NMEA_ERR_INVALID_ARGUMENT;
    }

    if (buff[0] == '\0') {
        return NMEA_OK;
    }

    switch (index) {
    case 1:
        gga_msg->utc_time = atof(buff);
        break;
    case 2:
        gga_msg->latitude = atof(buff);
        break;
    case 3:
        gga_msg->lat_dir = buff[0];
        break;
    case 4:
        gga_msg->longitude = atof(buff);
        break;
    case 5:
        gga_msg->lon_dir = buff[0];
        break;
    case 6:
        gga_msg->quality = (uint8_t)atoi(buff);
        break;
    case 7:
        gga_msg->satellites = (uint8_t)atoi(buff);
        break;
    case 8:
        gga_msg->hdop = atof(buff);
        break;
    case 9:
        gga_msg->altitude = atof(buff);
        break;
    case 10:
        gga_msg->alt_uom = buff[0];
        break;
    case 11:
        gga_msg->geoid_sep = atof(buff);
        break;
    case 12:
        gga_msg->geoid_uom = buff[0];
        break;
    case 13:
        gga_msg->dgps_age = atof(buff);
        break;
    case 14:
        gga_msg->station_id = (uint16_t)atoi(buff);
        break;
    default:
        return NMEA_ERR_INVALID_INDEX;
        break;
    }

    return NMEA_OK;
}

enum NmeaErrCodes parse_gga(struct GGA *gga_msg, const char *s)
{
    if (gga_msg == NULL || s == NULL) {
        return NMEA_ERR_INVALID_ARGUMENT;
    }

    if (s[0] != '$' || strlen(s) < 7) {
        return NMEA_ERR_BAD_STRING;
    }

    enum NmeaErrCodes checksum = validate_checksum(s);

    if (checksum != NMEA_OK) {
        return NMEA_ERR_BAD_CHECKSUM;
    }

    char tmp_buff[BUFF_SIZE];
    size_t curr_buff_size = 0;
    uint8_t curr_field = 1;
    enum NmeaErrCodes assign_succ = NMEA_OK;

    /* Skipping the message id. A function should return the index */
    /* of the first field after the message id field.              */
    size_t i = 7;

    for (; s[i] != '*' && s[i] != 0; i++) {

        if (s[i] != ',' && curr_buff_size < BUFF_SIZE - 1) {

            tmp_buff[curr_buff_size] = s[i];
            curr_buff_size += 1;

        } else if (curr_buff_size >= BUFF_SIZE -1) {
            return NMEA_ERR_BUFFER_OVERFLOW;
        } else if (s[i] == ',') {

            tmp_buff[curr_buff_size] = '\0';

            assign_succ = assign_gga_field(gga_msg, tmp_buff, curr_field);

            if (assign_succ != NMEA_OK) {
                return NMEA_ERR_BAD_ASSIGNMENT;
            }

            curr_field += 1;

            curr_buff_size = 0;
        }

        if(curr_field > MAX_GGA_FIELDS) {
            return NMEA_ERR_TOO_MANY_FIELDS;
        }
    } // for

    tmp_buff[curr_buff_size] = '\0';

    assign_succ = assign_gga_field(gga_msg, tmp_buff, curr_field);

    if (assign_succ != NMEA_OK) {
        return NMEA_ERR_BAD_ASSIGNMENT;
    }

    return NMEA_OK;
}
