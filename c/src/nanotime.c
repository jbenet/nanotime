#include <string.h>
#include <stdio.h>
#include "nanotime.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif


#define kT_ns_in_s  (uint64_t)1000000000
#define kT_ns_in_us (uint64_t)1000
#define kT_ns_in_day (int64_t)86400000000000

static int64_t utc_nanosecond_offset = (int64_t)kT_ns_in_day; /* sentinel */


uint64_t nanotime_sec(const struct nanotime *nt) {
  return nt->ns / kT_ns_in_s;
}

uint64_t nanotime_usec(const struct nanotime *nt) {
  return nt->ns / kT_ns_in_us;
}

// to follow the c++ api.
uint64_t nanotime_nsec(const struct nanotime *nt) {
  return nt->ns;
}




struct nanotime nanotime_from_sec(const uint64_t sec) {
  struct nanotime nt;
  nt.ns = sec * kT_ns_in_s;
  return nt;
}

struct nanotime nanotime_from_sec_f(const long double sec) {
  struct nanotime nt;
  nt.ns = sec * kT_ns_in_s;
  return nt;
}

struct nanotime nanotime_from_usec(const uint64_t usec) {
  struct nanotime nt;
  nt.ns = usec * kT_ns_in_us;
  return nt;
}

struct nanotime nanotime_from_nsec(const uint64_t nsec) {
  struct nanotime nt;
  nt.ns = nsec;
  return nt;
}




// to follow the c++ api.
struct timeval nanotime_timeval(const struct nanotime *nt) {
  struct timeval tv;
  tv.tv_sec = nanotime_sec(nt);
  tv.tv_usec = nanotime_usec(nt) % kT_ns_in_us;
  return tv;
}

struct timespec nanotime_timespec(const struct nanotime *nt) {
  struct timespec ts;
  ts.tv_sec = nanotime_sec(nt);
  ts.tv_nsec = nt->ns % kT_ns_in_s;
  return ts;
}

struct nanotime nanotime_from_timeval(const struct timeval *tv) {
  struct nanotime nt;
  nt.ns = (tv->tv_sec * kT_ns_in_s) + (tv->tv_usec * kT_ns_in_us);
  return nt;
}

struct nanotime nanotime_from_timespec(const struct timespec *ts) {
  struct nanotime nt;
  nt.ns = (ts->tv_sec * kT_ns_in_s) + (ts->tv_nsec);
  return nt;
}



/* NOTE: the following juggling between UTC and local times is necessary */
/* in order to account for hosts potentially setting INCORRECT timezones */
/* for this, the nanotime interface exposes setting nanotime_utc_offset  */

struct nanotime nanotime_now() {
  struct timespec ts;

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts.tv_sec = mts.tv_sec;
  ts.tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, &ts);
#endif

  ts.tv_sec += host_utc_sec_offset();
  return nanotime_from_timespec(&ts);
}





/* fast access to UTC nanotime. must remember to call  */
struct nanotime nanotime_utc_now() {
  struct nanotime nt = nanotime_now();
  return nanotime_utc_from_local(&nt);
}


struct nanotime nanotime_utc_from_local(const struct nanotime *nt) {
  return nanotime_from_nsec(nt->ns - nanotime_utc_offset());
}

struct nanotime nanotime_local_from_utc(const struct nanotime *nt) {
  return nanotime_from_nsec(nt->ns + nanotime_utc_offset());
}





int64_t host_utc_sec_offset() {
  time_t secs = (time_t)time(NULL);
  struct tm tm_;
  localtime_r(&secs, &tm_);
  return (int64_t)tm_.tm_gmtoff;
}

int64_t nanotime_utc_offset() {
  if (utc_nanosecond_offset >= kT_ns_in_day) { // sentinel
    nanotime_utc_offset_is(host_utc_sec_offset() * kT_ns_in_s);
  }
  return utc_nanosecond_offset;
}


void nanotime_utc_offset_is(const int64_t offset) {
  utc_nanosecond_offset = offset;
}





/* fill buffer `buf` with up to `len` chars of the iso representation of `nt`*/
/* including a null terminating byte. This function behaves like snprintf.   */
/* e.g.: "2011-09-11 05:50:50.576621"  would need a buffer of size 27        */
/* returns how many chars were printed (not including the trailing '\0')     */
/* may be less than `len` for cases where nanoseconds couldn't fit           */
size_t nanotime_iso(const struct nanotime *nt, char *buf, const size_t len) {
  memset(buf, '\0', len);

  time_t secs = (time_t)nanotime_sec(nt);
  struct tm tm_;
  gmtime_r(&secs, &tm_);
  size_t offset = strftime(buf, len, "%Y-%m-%d %H:%M:%S", &tm_);

  offset += snprintf(buf + offset, len - offset, ".%llu",
      (long long unsigned)(nt->ns % kT_ns_in_s) / kT_ns_in_us);
  return offset;
}




#undef kT_ns_in_s
#undef kT_ns_in_us
#undef kT_ns_in_day
