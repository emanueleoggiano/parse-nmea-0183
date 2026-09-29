#include <stddef.h>
#include <stdint.h>

#include "nmea_errors.h"
#include "nmea_types.h"
#include "nmea_parser.h"
#include "protocols/zda.h"

#define BUFF_SIZE 30


enum NmeaErrCodes initialize_zda(struct ZDA *msg)
{
	if (msg == NULL) {
		return NMEA_ERR_INVALID_ARGUMENT;
	}

	msg->utc_time = -9999.0;

	msg->year = UINT16_MAX;
	msg->hour_gmt_offset = INT8_MAX;
	msg->min_gmt_offset = INT8_MAX;
	msg->day = INT8_MAX;
	msg->month = INT8_MAX;

	return NMEA_OK;
}
enum NmeaErrCodes assign_zda_field(struct ZDA *msg, const char *buff, size_t index)
{
	if (msg == NULL || buff == NULL) {
		return NMEA_ERR_INVALID_ARGUMENT;
	}

	if (buff[0] == '\0') {
		return NMEA_OK;
	}

	switch(index) {
	case 1:
		msg->utc_time = atof(buff);
		break;
	case 2:
		msg->year = (uint16_t)atoi(buff);
		break;
	case 3:
		msg->hour_gmt_offset = (int8_t)atoi(buff);
		break;
	case 4:
		msg->min_gmt_offset = (uint8_t)atoi(buff);
		break;
	case 5:
		msg->day = (uint8_t)atoi(buff);
		break;
	case 6:
		msg->month = (uint8_t)atoi(buff);
		break;
	default:
		return NMEA_ERR_INVALID_INDEX;
		break;
	}

	return NMEA_OK;
}


enum NmeaErrCodes parse_zda(struct ZDA *msg, const char *s)
{
	if (msg == NULL || s == NULL) {
		return NMEA_ERR_INVALID_ARGUMENT;
	}

	if (s[0] != '$') {
		return NMEA_ERR_BAD_STRING;
	}

	size_t first_field_index = 0;
	size_t curr_buff_size = 0;
	char tmp_buff[BUFF_SIZE];
	uint8_t curr_field = 1;
	enum NmeaErrCodes status = skip_msg_id(s, &first_field_index);

	if (status != NMEA_OK) {
		return NMEA_ERR_BAD_STRING;
	}

	status = validate_checksum(s);

	if (status != NMEA_OK) {
		return NMEA_ERR_BAD_CHECKSUM;
	}

	for (size_t i = first_field_index; s[i] != '*' && s[i] != 0; i++) {

		if (s[i] != ',' && curr_buff_size < BUFF_SIZE - 1) {
			
			tmp_buff[curr_buff_size] = s[i];
			curr_buff_size += 1;

		} else if (curr_buff_size > BUFF_SIZE - 1) {
			return NMEA_ERR_BUFFER_OVERFLOW;
		} else if (s[i] == ',') {

			tmp_buff[curr_buff_size] = '\0';

			status = assign_zda_field(msg, tmp_buff, curr_field);

			if (status != NMEA_OK) {
				return NMEA_ERR_BAD_ASSIGNMENT;
			}

			curr_field += 1;
			curr_buff_size = 0;
		}

		if (curr_field > MAX_ZDA_FIELDS) {
			return NMEA_ERR_TOO_MANY_FIELDS;
		}
	} // for

	tmp_buff[curr_buff_size] = '\0';

	status = assign_zda_field(msg, tmp_buff, curr_field);

	if (status != NMEA_OK) {
	   return NMEA_ERR_BAD_ASSIGNMENT;
    }

	return NMEA_OK;
}
