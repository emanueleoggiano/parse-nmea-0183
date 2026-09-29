# NMEA-0183 Parser

A zero allocations, fail fast C parser for NMEA-0183 data. It focuses on memory safety and strict error handling.

## Supported messages

Right now, the only supported message is `GGA`. Other types of messages will be supported in future.

## Setup

The project uses Makefile. In order to compile type `make` and it will generate the binary (`nmea_parser`).
No external dependencies are required.

## How does it work

## Documentation

* [Trimble](https://receiverhelp.trimble.com/alloy-gnss/en-us/NMEA-0183messages_MessageOverview.html)

## License

This project has been released under the BSD 3-Clause License.
