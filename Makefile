CC = gcc
CFLAGS = -std=c99 -W -Wall -Wextra -pedantic -Wshadow -Wstrict-prototypes \
         -Wmissing-prototypes -Wconversion -Wundef -fstack-protector-strong \
         -D_FORTIFY_SOURCE=2 -Wstack-usage=2048 -fno-common -Werror -O3 \
         -Iinclude -Isrc

SRCS = $(wildcard src/*.c) $(wildcard src/protocols/*.c)

TARGET = nmea_parser

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
