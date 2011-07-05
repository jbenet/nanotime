# Nanotime

### nanosecond precision time

Nanotime provides a time object that keeps time as the number of nanoseconds
since the UNIX epoch. In other words, it is a 64bit UNIX timestamp with
nanosecond precision.

[https://github.com/jbenet/nanotime](https://github.com/jbenet/nanotime)

## Why yet another time type!?

Over and over, I found the need for a portable, easy to process time type. The
good old Unix timestamp was perfect except for the lack of precision. Finding no
better alternative, I decided to make my own to fit my needs: a uint64 count of nanoseconds since the unix epoch.

### What about `timespec` and `timeval`?
While `timevals` and `timespecs` add the much needed precision (`usec` and
`nsec`), they do so in a cumbersome way. They store the extra precision in
a second `uint32` rather than in one whole field. While this preserves quick
access to the `sec` part of the time value, adding and subtracting `timespecs`
and `timevals` is not as simple as integer operations. For most of my use cases,
I found myself comparing, adding, subtracting time values much more than
outputting them. Furthermore, I tend to require the sub-second precision when
printing out, storing, and transferring (or anything else the `sec` field used
to satisfy) anyway.

### What about ISO? It's perfectly portable and searchable!
And slow and heavy. Sometimes you want a lighter and faster type, for quick
comparisons of lots of data (entry bookkeeping, packet timestamping).

### What about [http://msdn.microsoft.com/en-us/library/system.datetime.aspx](MS DateTime)?
While DateTime does store the...entire number in one field, they chose to count
the odd measure of 100-nanosecond intervals (dubbed `ticks`, not to be confused
with processor ticks). If this weren't enough, MS DateTime also starts off from
the year 0000 AD, since they could never bear to use the Unix Epoch. While I'm
all for multi-millennia software, this introduces the cumbersome problems of
leap seconds and calendar uncertainty.


### Range:

2 ^ 64 nanoseconds is roughly ~ 584.554531 years. The timespan between 1970 to 2554 is more than enough for me.

Then again, it may be best to use a range of 292 around 1970. If I find the need to go much earlier than 1970 in a non-textual representation, I may revise this.

## Implementations

There are currently implementations in:

 * C  -- struct nanotime
 * C++  -- nanotime::Time
 * Python  -- nanotime

included in this source.

## License

Nanotime is under the MIT License.



