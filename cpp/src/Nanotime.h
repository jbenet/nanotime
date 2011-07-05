#ifndef __NANOTIME_H__
#define __NANOTIME_H__

#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>

#include "Nominal.h"

#define kT_ns_in_s  (uint64_t)1000000000
#define kT_ns_in_us (uint64_t)1000

namespace nanotime {

using namespace Fwk;

/* Define the type 'Time': UNIX timestamp with microsecond precision. */
class Time : public Ordinal<Time, uint64_t> {
public:

  Time() : Ordinal<Time, uint64_t>(0) {}

  Time(const struct timeval &_time) : Ordinal<Time, uint64_t>(
    (_time.tv_sec * kT_ns_in_s) + (_time.tv_usec * kT_ns_in_us)) {}

  Time(const struct timespec &_time) : Ordinal<Time, uint64_t>(
    (_time.tv_sec * kT_ns_in_s) + (_time.tv_nsec)) {}

  inline uint64_t  sec() const { return value_ / kT_ns_in_s; }
  inline uint64_t usec() const { return value_ / kT_ns_in_us; }
  inline uint64_t nsec() const { return value_; }

  inline std::string isoString() const {
    char buf[32] = {0};

    time_t secs = (time_t)sec();
    tm tm_;
    gmtime_r(&secs, &tm_);
    size_t offset = strftime(buf, 32, "%Y-%m-%d %H:%M:%S", &tm_);

    if (offset < 25)
      sprintf(buf + offset, ".%llu", (value_ % kT_ns_in_s) / kT_ns_in_us);

    return std::string(buf);
  }

  static inline Time now() {
    #ifndef __LINUX__
      struct timeval tv; gettimeofday(&tv, NULL); return tv;
    #else
      struct timespec ts; clock_gettime(CLOCK_REALTIME, &ts); return ts;
    #endif
  }

  static inline Time nsec(const uint64_t &_t) {
    return Time(_t);
  }

  static inline Time usec(const uint64_t &_t) {
    return Time(_t * kT_ns_in_us);
  }

  static inline Time sec(const uint64_t &_t) {
    return Time(_t * kT_ns_in_s);
  }

  static inline Time sec(const double &_t) {
    return Time::sec((long double)_t);
  }

  static inline Time sec(const long double &_t) {
    return Time(static_cast<uint64_t>((_t * kT_ns_in_s)));
  }

  inline bool operator==(const uint64_t &_val) {
    return value_ == _val;
  }

  inline bool operator==(const Time &_time) {
    return value_ == _time.value_;
  }

  inline uint64_t value() const {
    return value_;
  }

  Time operator+(const Time& other) const {
    return Time(Nominal<Time, uint64_t>::value_ + other.value_);
  }

  Time operator+=(const Time& other) {
    Nominal<Time, uint64_t>::value_ += other.value_;
    return *this;
  }

  Time operator-(const Time& other) const {
    return Time(Nominal<Time, uint64_t>::value_ - other.value_);
  }

  Time operator-=(const Time& other) {
    Nominal<Time, uint64_t>::value_ -= other.value_;
    return *this;
  }

  Time operator/(const Time& other) const {
    return Time(Nominal<Time, uint64_t>::value_ / other.value_);
  }

  operator Time() const {
    return Time(Nominal<Time, uint64_t>::value_);
  }


protected:
  explicit Time(const uint64_t &_time) : Ordinal<Time, uint64_t>(_time) {}

};

inline std::ostream & operator<<( std::ostream &_stream, Time const &_time) {
  // _stream << _time.sec() << "." << (_time.nsec() % kT_ns_in_s) ;
  _stream << _time.isoString();
  return _stream;
}

} // end namespace nanotime

#undef kT_ns_in_s
#undef kT_ns_in_us

#endif // __NANOTIME_H__
