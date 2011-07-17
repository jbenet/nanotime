

CC        = gcc
CFLAGS    = -Wall -O2 -std=gnu99
LDFLAGS   =
INCFLAGS  = -I./src

UNAME     = $(shell uname -s)

ifneq ($(UNAME), Darwin)
LDFLAGS   := $(LDFLAGS) -lrt -lc
endif


SRCS      = src/nanotime.c
TESTS     = test_nanotime
RUN_TESTS = ${patsubst %,run_%,$(TESTS)}



.PHONY: all test check clean

all: test

clean:
	rm -rf build/*

check: test

test: build $(RUN_TESTS)

test_%: test/test_%.c
	$(CC) $(CFLAGS) -o build/$@ $^ $(SRCS) $(INCFLAGS) $(LDFLAGS)

run_% : %
	@echo '==============> running $<'
	@build/$< > /dev/null

build:
	@mkdir build
