# NMEA-0183 Parser

A zero allocations, fail fast C parser for NMEA-0183 data. It focuses on memory safety and strict error handling.

## Key Principles

* **No usage of Dynamic Memory** (`malloc`, `free`)
* **Fail Fast Implementation**: before anny parsing attempt the code will valide the checksum

## Supported Messages

Right now, the only supported message is `GGA`. Other types of messages will be supported in future.

## Setup

The project uses Makefile. No external dependencies are required.

```bash
# First clone the repo

git clone [https://github.com/emanueleoggiano/parse-nmea-0183.git](https://github.com/emanueleoggiano/parse-nmea-0183.git)
cd parse-nmea-0183

# Then build the project (compilation of the parser and the main.c file which contains an example of usage)

make

# Run the parser

./nmea_parser

```

## Examples of usage

First of all you must include all the libraries inside the include folder.
```C
#include "nmea_errors.h"
#include "nmea_parser.h"
#include "nmea_types.h"
#include "nmea_protocols.h"
```

Then you have to declare two structures: an NmeaErrCodes enum, which will be used to check potential errors, and the message struct (in this particular case the GGA struct).
```C
enum NmeaErrCodes status;
struct GGA msg;
```

You must initialize your struct with default data
```C
status = initialize_gga(&msg);
```

After checking the status, you can safely parse your NMEA-0183 string
```C
status = parse_gga(&msg, nmea_string);
```

## Documentation

* [Trimble](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_MessageOverview.html)

## License

This project has been released under the BSD 3-Clause License. Please read [LICENSE](https://github.com/emanueleoggiano/parse-nmea-0183/blob/main/LICENSE) for the details.
