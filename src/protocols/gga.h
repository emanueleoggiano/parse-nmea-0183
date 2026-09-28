#ifndef GGA_H
#define GGA_H

#define MAX_GGA_FIELDS 14

enum NmeaErrCodes initialize_gga(struct GGA *gga_msg);
static enum NmeaErrCodes assign_gga_field(struct GGA *gga_msg, const char *buff, size_t index);
enum NmeaErrCodes parse_gga(struct GGA *gga_msg, const char *s);

#endif // GGA_H
