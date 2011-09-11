#import <stdio.h>
#import <string.h>
#import <unistd.h>

#import "NSDate+Nanotime.h"

static int errors = 0;
static const char *kINDENT = "-----> ";
static const int float_tolerance = 1000;
#define interval_tolerance (float_tolerance / 1000000000.0)


#define DOT printf(".")
#define massert(cond, msg) if (!(cond)) \
fprintf(stderr, "Error %d [" __FILE__ ":%d]: %s \n", ++errors, __LINE__, msg);\


bool fct_close(uint64_t ns1, uint64_t ns2) {
  return abs(ns1 - ns2) < float_tolerance;
}


void test_creation_time(uint32_t sec, uint32_t usec, const char *isostr) {
  printf("--> testing %s -- %d.%d \n", isostr, sec, usec);

  uint64_t useci = (uint64_t)(sec) * 1000000 + usec;


  // #pragma warning Testing double disabled to rounding errors!
  nanotime nt1 = nanotime_from_usec(useci);

  NSTimeInterval ti1 = (sec) + (usec / 1000000.0);
  NSTimeInterval ti2 = [NSDate timeIntervalWithNanotimeSince1970:nt1];

  NSDate *d1 = [NSDate dateWithTimeIntervalSince1970:ti1];
  NSDate *d2 = [NSDate dateWithTimeIntervalSince1970:ti2];
  NSDate *d3 = [NSDate dateWithNanotimeSince1970:nt1];

  NSTimeInterval ti3 = (sec) + (usec / 1000000.0);
  NSTimeInterval ti4 = [NSDate timeIntervalWithNanotimeSince1970:nt1];

  nanotime nt2 = [NSDate nanotimeWithTimeIntervalSince1970:ti1];
  nanotime nt3 = [NSDate nanotimeWithTimeIntervalSince1970:ti2];
  nanotime nt4 = [d1 nanotimeSince1970];
  nanotime nt5 = [d2 nanotimeSince1970];
  nanotime nt6 = [d3 nanotimeSince1970];

  massert(nanotime_usec(&nt1) == useci, "nanotimes (usec) should be equal. ");

  massert(fabs(ti1 - ti2) <= interval_tolerance, "intervals should be equal. ");
  massert(fabs(ti1 - ti3) <= interval_tolerance, "intervals should be equal. ");
  massert(fabs(ti1 - ti4) <= interval_tolerance, "intervals should be equal. ");

  printf("nsti drift: %.10lf \n", [d1 timeIntervalSinceDate:d2]);
  printf("nsti drift: %.10lf \n", [d1 timeIntervalSinceDate:d3]);
  printf("nsti drift: %.10lf \n", [d2 timeIntervalSinceDate:d3]);

  massert(fabs([d1 timeIntervalSinceDate:d2]) <= interval_tolerance, "dates");
  massert(fabs([d1 timeIntervalSinceDate:d3]) <= interval_tolerance, "dates");
  massert([d2 isEqualToDate:d3], "dates should be equal. ");

  massert(nanotime_usec(&nt1) == useci, "nanotimes (usec) should be equal. ");
  massert(fct_close(nt2.ns, useci*1000), "nanotimes (usec) should be equal. ");
  massert(fct_close(nt3.ns, useci*1000), "nanotimes (usec) should be equal. ");
  massert(fct_close(nt4.ns, useci*1000), "nanotimes (usec) should be equal. ");
  massert(fct_close(nt5.ns, useci*1000), "nanotimes (usec) should be equal. ");
  massert(fct_close(nt6.ns, useci*1000), "nanotimes (usec) should be equal. ");

  massert(fct_close(nt1.ns, nt2.ns), "nanotimes (nsec) should be equal. ");
  massert(fct_close(nt1.ns, nt3.ns), "nanotimes (nsec) should be equal. ");
  massert(fct_close(nt1.ns, nt4.ns), "nanotimes (nsec) should be equal. ");
  massert(fct_close(nt1.ns, nt5.ns), "nanotimes (nsec) should be equal. ");
  massert(fct_close(nt1.ns, nt6.ns), "nanotimes (nsec) should be equal. ");

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

  nanotime nt1 = [[NSDate date] nanotimeSince1970];

  usleep(1); // yes, code is that fast.

  nanotime nt2 = nanotime_utc_now();

  massert(nt1.ns <  nt2.ns, "time1 should be smaller than time2");
  massert(nt1.ns != nt2.ns, "time1 should not be equal to time2");
  massert(nt2.ns >  nt1.ns, "time2 should be greater than time1");

}


int main(int argc, char **argv) {

  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  fprintf(stderr, ">>> float conversion tolerance: %d nanoseconds\n",
    float_tolerance);
  fprintf(stderr, ">>> seems high, but even trivial examples need it...\n");
  test_creation();
  test_now();
  printf("\n Finished (%d errors).\n", errors);

  [pool release];
  return 0;
}