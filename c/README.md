# Nanotime

### nanosecond precision time

The nanotime module provides a time object that keeps time as the number of
nanoseconds since the UNIX epoch. In other words, it is a 64bit UNIX timestamp
with nanosecond precision.

[https://github.com/jbenet/nanotime](https://github.com/jbenet/nanotime)

## License

Nanotime is under the MIT License.

## Usage

Place both nanotime.h and nanotime.c along with your other sources. nanotime in
c is currently defined as `struct nanotime`. This follows suit with common c
practice, as well as `struct timespec` and `struct timeval.`

## Tests

There is one basic test file so far. Run with:

    make test

