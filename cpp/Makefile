

CXX       = g++
CFLAGS    = -Wall -O2
INCFLAGS  = -I./src


TESTS     = test_nanotime
RUN_TESTS = ${patsubst %,run_%,$(TESTS)}



.PHONY: all test check clean

all: test

clean:
	rm -rf build/*

check: test

test: $(RUN_TESTS)

test_%: test/test_%.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(INCFLAGS)

run_% : %
	@echo '==============> running $<'
	@./$< > /dev/null
