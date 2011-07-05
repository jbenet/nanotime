# Nanotime

### nanosecond precision time

The nanotime module provides a time object that keeps time as the number of
nanoseconds since the UNIX epoch. In other words, it is a 64bit UNIX timestamp
with nanosecond precision.

[https://github.com/jbenet/nanotime](https://github.com/jbenet/nanotime)

## Install

    sudo python setup.py install

## License

Nanotime is under the MIT License.

## Usage

simple:

    >>> import nanotime
    >>> nanotime.now()
    nanotime.nanotime(1309847805647559936)
    >>> str(nanotime.now())
    '2011-07-04 23:36:59.694926080'

conversions:

    >>> nanotime.seconds(100)
    nanotime.nanotime(100000000000)

    >>> import datetime
    >>> nanotime.datetime(datetime.datetime.now())
    nanotime.nanotime(1309847995629583872)

    >>> import time
    >>> nanotime.timestamp(time.time())
    nanotime.nanotime(1309849172822870016)

## Tests

There is one basic test file so far. Run with:

    nosetests

