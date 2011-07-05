

CC        = gcc
CFLAGS    = -Wall -O2 -std=c99
INCFLAGS  = -I./src


SRCS      = src/nanotime.c
TESTS     = test_nanotime
RUN_TESTS = ${patsubst %,run_%,$(TESTS)}



.PHONY: all test check clean

all: test

clean:
	rm -rf build/*

check: test

test: $(RUN_TESTS)

test_%: test/test_%.c
	$(CC) $(CFLAGS) -o build/$@ $^ $(SRCS) $(INCFLAGS)

run_% : %
	@echo '==============> running $<'
	@build/$< > /dev/null
