# Nanotime

### nanosecond precision time

The nanotime module provides a time object that keeps time as the number of
nanoseconds since the UNIX epoch. In other words, it is a 64bit UNIX timestamp
with nanosecond precision.

[https://github.com/jbenet/nanotime](https://github.com/jbenet/nanotime)

## License

Nanotime is under the MIT License.

## Usage

This Obj-C implementation is based on the C implementaion, with the addition of
a category on NSDate.

Place nanotime.h, nanotime.c, NSDate+nanotime.h, NSDate+nanotime.m along with your other sources. This implementation uses a typedefs nanotime.


    > nanotime ntime = nanotime_now();
    > printf("%llu", ntime.ns);
    1303772832961549000

    > NSDate *date = [NSDate dateWithNanotimeSince1970:ntime];
    > NSLog(@"%@", date);
    2011-04-25 16:07:12


### Warning -- NSDate conversions lose precision

Due to how NSDate works, conversions go through NSTimeInterval (float) which
causes a loss of precision. I've seen this loss as high as `2 usec` so far. To
bypass this, use the C interface directly (only uint64s) when the precision
(or equality) is necessary.

## Tests

There is one basic test file so far. Run with:

    make test

