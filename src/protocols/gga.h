#ifndef GGA_H
#define GGA_H

#define MAX_GGA_FIELDS 14

NmeaErrCodes initialize_gga(struct GGA *gga_msg);
NmeaErrCodes assign_gga_field(struct GGA *gga_msg, const char *buff, size_t index);
NmeaErrCodes parse_gga(struct GGA *gga_msg, const char *s);

#endif // GGA_H
