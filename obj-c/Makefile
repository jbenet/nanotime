

CC        = gcc
CFLAGS    = -Wall -O2 -std=c99
INCFLAGS  = -I./src
OBJC      = -lobjc -framework Foundation


C_SRCS    = src/nanotime.c
O_SRCS    = $(C_SRCS) src/NSDate+Nanotime.m

TESTS     = test_nanotime test_nsdate
RUN_TESTS = ${patsubst %,run_%,$(TESTS)}



.PHONY: all test check clean

all: build test

build:
	@mkdir build

clean:
	rm -rf build/*

check: test

test: build $(RUN_TESTS)


test_%: test/test_%.m
	$(CC) $(CFLAGS) -o build/$@ $^ $(O_SRCS) $(INCFLAGS) $(OBJC)


run_% : %
	@echo '==============> running $<'
	@build/$< > /dev/null
