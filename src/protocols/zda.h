#ifndef ZDA_H
#define ZDA_H

#define MAX_ZDA_FIELDS 6

NmeaErrCodes initialize_zda(ZDA *msg);
NmeaErrCodes assign_zda_field(ZDA *msg, const char *buff, size_t index);
NmeaErrCodes parse_zda(ZDA *msg, const char *s);

#endif // ZDA_H
