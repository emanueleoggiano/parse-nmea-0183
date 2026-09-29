#ifndef ZDA_H
#define ZDA_H

#define MAX_ZDA_FIELDS 6

enum NmeaErrCodes initialize_zda(struct ZDA *msg);
enum NmeaErrCodes assign_zda_field(struct ZDA *msg, const char *buff, size_t index);
enum NmeaErrCodes parse_zda(struct ZDA *msg, const char *s);

#endif // ZDA_H
