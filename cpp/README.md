# Nanotime

### nanosecond precision time

The nanotime module provides a time object that keeps time as the number of
nanoseconds since the UNIX epoch. In other words, it is a 64bit UNIX timestamp
with nanosecond precision.

[https://github.com/jbenet/nanotime](https://github.com/jbenet/nanotime)

## License

Nanotime is under the MIT License.

## Usage

Place both Nanotime.h and Nominal.h along with your other sources. You may find
Nominal useful as well.

Currently, the type you want is `nanotime::Time`. This may change in the future
to one either `nanotime::nanotime` or just `nanotime`.

## Tests

There is one basic test file so far. Run with:

    make test

