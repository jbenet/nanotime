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

/* fast access to UTC nanotime. must remember to call  */
struct nanotime nanotime_utc_now();
struct nanotime nanotime_utc_from_local(const struct nanotime *nt);
struct nanotime nanotime_local_from_utc(const struct nanotime *nt);

/* in order to account for hosts potentially setting INCORRECT timezones */
/* the nanotime interface exposes setting nanotime_utc_offset            */
void nanotime_utc_offset_is(const int64_t offset);
int64_t nanotime_utc_offset();
int64_t host_utc_sec_offset();


/* fill buffer `buf` with up to `len` chars of the iso representation of `nt`*/
/* including a null terminating byte. This function behaves like snprintf.   */
/* e.g.: "2011-09-11 05:50:50.576621"  would need a buffer of size 27        */
/* returns how many chars were printed (not including the trailing '\0')     */
/* may be less than `len` for cases where nanoseconds couldn't fit           */
size_t nanotime_iso(const struct nanotime *nt, char *buf, const size_t len);


#endif /* __NANOTIME_C_H__ */
