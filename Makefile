CC ?= gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LDLIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

SRC = ttoolbox.c

OBJS = $(SRC:.c=.o)

all: ttoolbox

%.o: %.c
	$(CC) -c -o $(@F) $(CFLAGS) $<

example0: $(OBJS)
	$(CC) -o $(@F) $(LIBS) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f ttoolbox