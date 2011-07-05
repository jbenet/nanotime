#ifndef __NANOTIME_C_H__
#define __NANOTIME_C_H__

#include <time.h>
#include <sys/time.h>
#include <stdint.h>


struct nanotime {
  uint64_t ns;
};


/* convert from nanotime into others */
uint64_t nanotime_sec(const struct nanotime *nt);
uint64_t nanotime_usec(const struct nanotime *nt);
uint64_t nanotime_nsec(const struct nanotime *nt); // to follow the c++ api.

struct timeval nanotime_timeval(const struct nanotime *nt);
struct timespec nanotime_timespec(const struct nanotime *nt);


/* convert from others into nanotime */
struct nanotime nanotime_from_sec(const uint64_t sec);
struct nanotime nanotime_from_sec_f(const long double sec);
struct nanotime nanotime_from_usec(const uint64_t usec);
struct nanotime nanotime_from_nsec(const uint64_t nsec);

struct nanotime nanotime_from_timeval(const struct timeval *tv);
struct nanotime nanotime_from_timespec(const struct timespec *ts);


/* fast access to current time */
struct nanotime nanotime_now();


/* fill buffer `buf` with up to `len` chars of the iso representation of `nt` */
/* returns how many chars were printed into the buffer.                       */
/* may be less than `len` for cases where nanoseconds couldn't fit            */
size_t nanotime_iso(const struct nanotime *nt, char *buf, const size_t len);


#endif // __NANOTIME_C_H__
