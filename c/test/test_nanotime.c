#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "nanotime.h"

static const char *kINDENT = "-----> ";
static int errors = 0;

#define DOT printf(".")
#define massert(cond, msg) if (!(cond)) \
fprintf(stderr, "Error %d [" __FILE__ ":%d]: %s \n", __LINE__, ++errors, msg);\



void test_creation_time(uint32_t sec, uint32_t usec, const char *isostr) {
  printf("--> testing %s -- %d.%d \n", isostr, sec, usec);

  uint64_t useci = (uint64_t)(sec) * 1000000 + usec;

  struct timeval tval;
  tval.tv_sec = sec;
  tval.tv_usec = usec;

  struct timespec tspec;
  tspec.tv_sec = sec;
  tspec.tv_nsec = usec * 1000;

  // #pragma warning Testing double disabled to rounding errors!
  struct nanotime t1 = nanotime_from_usec(useci);
  // Time t2 = Time::sec(secd);
  struct nanotime t3 = nanotime_from_timeval(&tval);
  struct nanotime t4 = nanotime_from_nsec(t1.ns);
  struct nanotime t5 = nanotime_from_timespec(&tspec);
  struct nanotime t6 = nanotime_from_nsec(useci * 1000);

  massert(nanotime_usec(&t1) == useci, "times should be equal. ");
  massert(nanotime_usec(&t3) == useci, "times should be equal. ");
  massert(nanotime_usec(&t4) == useci, "times should be equal. ");
  massert(nanotime_usec(&t5) == useci, "times should be equal. ");
  massert(nanotime_usec(&t6) == useci, "times should be equal. ");

  massert(t1.ns == t3.ns, "times should be equal. ");
  massert(t1.ns == t4.ns, "times should be equal. ");
  massert(t1.ns == t5.ns, "times should be equal. ");
  massert(t1.ns == t6.ns, "times should be equal. ");

  char buf[26];
  massert(nanotime_iso(&t1, buf, 26) == 26, "length");
  massert(strcmp(buf, isostr) == 0, "should be eq");
  // massert(nanotime_iso(&t2, buf, 32) == 32, "length");
  // massert(strcmp(buf, isostr) == 0, "should be eq");
  massert(nanotime_iso(&t3, buf, 26) == 26, "length");
  massert(strcmp(buf, isostr) == 0, "should be eq");
  massert(nanotime_iso(&t4, buf, 26) == 26, "length");
  massert(strcmp(buf, isostr) == 0, "should be eq");
  massert(nanotime_iso(&t5, buf, 26) == 26, "length");
  massert(strcmp(buf, isostr) == 0, "should be eq");
  massert(nanotime_iso(&t6, buf, 26) == 26, "length");
  massert(strcmp(buf, isostr) == 0, "should be eq");

  uint32_t usec_uint = (uint32_t)useci;

  struct nanotime t7 = nanotime_from_usec(usec_uint);
  struct nanotime t8 = nanotime_from_usec((unsigned int)useci); // trunc
  struct nanotime t9 = nanotime_from_usec((uint32_t)useci); // truncates


  massert(nanotime_usec(&t7) == usec_uint, "truncated times should be equal.");
  massert(nanotime_usec(&t8) == usec_uint, "truncated times should be equal.");
  massert(nanotime_usec(&t9) == usec_uint, "truncated times should be equal.");
  massert(t7.ns == t8.ns, "truncated times should be equal.");
  massert(t7.ns == t9.ns, "truncated times should be equal.");


}

void test_creation() {
  fprintf(stdout, "%s %s \n", kINDENT, __PRETTY_FUNCTION__);

  test_creation_time(1303772832, 961549, "2011-04-25 23:07:12.961549");
  test_creation_time(503, 123432, "1970-01-01 00:08:23.123432");
  test_creation_time(2303772832, 961549, "2043-01-02 00:53:52.961549");
  test_creation_time(172832, 961549, "1970-01-03 00:00:32.961549");
  test_creation_time(172832, 0, "1970-01-03 00:00:32.0");
  test_creation_time(0, 961549, "1970-01-01 00:00:00.961549");
  test_creation_time(0, 0, "1970-01-01 00:00:00.0");
}

void test_now() {
  fprintf(stdout, "%s %s \n", kINDENT, __PRETTY_FUNCTION__);

  struct timeval tval;
  gettimeofday(&tval, NULL);
  uint64_t usec = tval.tv_sec * 1e6 + tval.tv_usec;

  struct nanotime t1 = nanotime_from_timeval(&tval);
  struct nanotime t2 = nanotime_from_usec(usec);

  usleep(1); // yes, c is that fast.

  struct nanotime now = nanotime_now();

  massert(t1.ns < now.ns, "time1 should be less than time2");
  massert(t2.ns < now.ns, "time1 should be less than time2");
  massert(t1.ns == t2.ns, "time1 should be equal to time2");
  massert(now.ns > t1.ns, "time1 should be greater than time2");
  massert(now.ns > t2.ns, "time1 should be greater than time2");
  massert(t2.ns == t1.ns, "time1 should be equal to time2");

}

void test_arithmetic() {
  fprintf(stdout, "%s %s \n", kINDENT, __PRETTY_FUNCTION__);

  struct nanotime now = nanotime_now();
  struct nanotime us1 = nanotime_from_usec(1);
  struct nanotime now_p1;
  struct nanotime now_m1;
  now_p1.ns = now.ns + us1.ns;
  now_m1.ns = now.ns - us1.ns;


  massert(now.ns < now_p1.ns, "time1 should be less than time2");
  massert(now_m1.ns < now.ns, "time1 should be less than time2");
  massert(now_m1.ns < now_p1.ns, "time1 should be less than time2");

  massert(now.ns > now_m1.ns, "time1 should be greater than time2");
  massert(now_p1.ns > now.ns, "time1 should be greater than time2");
  massert(now_p1.ns > now_m1.ns, "time1 should be greater than time2");
}


int main(int argc, char **argv) {

  test_creation();
  test_now();
  test_arithmetic();

  printf("\n Finished (%d errors).\n", errors);

  return 0;
}