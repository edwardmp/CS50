#
# Makefile
#
# Edward M. Poot
# edwardmP@gmail.com
#
# Hacker 6
#

# compiler to use
CC = clang

# flags to pass compiler
CFLAGS = -ggdb -O0 -Qunused-arguments -std=c99 -Wall -Werror

# dump
DUMP = dump
DUMP_SRCS = dump.c forest.c huffile.c tree.c
DUMP_OBJS = $(DUMP_SRCS:.c=.o)

# huff
HUFF = huff
HUFF_SRCS = huff.c forest.c huffile.c tree.c
HUFF_OBJS = $(HUFF_SRCS:.c=.o)

# space-separated list of header files
HDRS = forest.h huffile.h tree.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = -lm

# target
$(HUFF): $(HUFF_OBJS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(HUFF_OBJS) $(LIBS)

$(DUMP): $(DUMP_OBJS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(DUMP_OBJS) $(LIBS)
	
# housekeeping
clean:
	rm -f core $(DUMP) $(HUFF) *.o
