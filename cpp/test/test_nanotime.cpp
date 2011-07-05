#include <iostream>
#include <string>

#include "Nanotime.h"

using namespace nanotime;
using namespace std;


static const char *kINDENT = "-----> ";
static int errors = 0;

#define DOT cout << "."
#define massert(cond, msg) if (!(cond)) cout << "Error " << ++errors << " [" << __FILE__ << ":" << __LINE__ << "]: " << msg << endl;


void testCreationTime(uint32_t sec, uint32_t usec, string isoString) {
  cout << "--> Testing " << isoString << " -- " << sec << "." << usec << endl;
  cout.flush();
  uint64_t useci = (uint64_t)(sec) * 1000000 + usec;
  // long double secd = sec + (usec / 1e6);

  struct timeval tval;
  tval.tv_sec = sec;
  tval.tv_usec = usec;

  struct timespec tspec;
  tspec.tv_sec = sec;
  tspec.tv_nsec = usec * 1000;

  // #pragma warning Testing double disabled to rounding errors!
  Time t1 = Time::usec(useci);
  // Time t2 = Time::sec(secd);
  Time t3 = Time(tval);
  Time t4 = Time(t1);
  Time t5 = Time(tspec);
  Time t6 = Time::nsec(useci * 1000);

  massert(t1.usec() == useci, "times should be equal. " << useci << t1.usec());
  // massert(t2.usec() == useci, "times should be equal. " << useci << t2.usec());
  massert(t3.usec() == useci, "times should be equal. " << useci << t3.usec());
  massert(t4.usec() == useci, "times should be equal. " << useci << t4.usec());
  massert(t5.usec() == useci, "times should be equal. " << useci << t5.usec());
  massert(t6.usec() == useci, "times should be equal. " << useci << t6.usec());

  // massert(t1 == t2, "times should be equal. " << t1 << " == " << t2);
  massert(t1 == t3, "times should be equal. " << t1 << " == " << t3);
  massert(t1 == t4, "times should be equal. " << t1 << " == " << t4);
  massert(t1 == t5, "times should be equal. " << t1 << " == " << t5);
  massert(t1 == t6, "times should be equal. " << t1 << " == " << t6);

  massert(t1.isoString() == isoString, "iso strings should be equal" << t1.isoString() << " == " << isoString);
  // massert(t2.isoString() == isoString, "iso strings should be equal");
  massert(t3.isoString() == isoString, "iso strings should be equal");
  massert(t4.isoString() == isoString, "iso strings should be equal");
  massert(t5.isoString() == isoString, "iso strings should be equal");
  massert(t6.isoString() == isoString, "iso strings should be equal");


  uint32_t usec_uint = (uint32_t)useci;

  Time t7 = Time::usec(usec_uint);
  Time t8 = Time::usec((unsigned int)useci); // truncates to usec_uint
  Time t9 = Time::usec((uint32_t)useci); // truncates to usec_uint

  massert(t7.usec() == usec_uint, "truncated times should be equal.");
  massert(t8.usec() == usec_uint, "truncated times should be equal.");
  massert(t9.usec() == usec_uint, "truncated times should be equal.");
  massert(t7 == t8, "truncated times should be equal.");
  massert(t7 == t9, "truncated times should be equal.");


}

void testCreation() {
  cout << kINDENT << __PRETTY_FUNCTION__ << endl;

  testCreationTime(1303772832, 961549, "2011-04-25 23:07:12.961549");
  testCreationTime(503, 123432, "1970-01-01 00:08:23.123432");
  testCreationTime(2303772832, 961549, "2043-01-02 00:53:52.961549");
  testCreationTime(172832, 961549, "1970-01-03 00:00:32.961549");
  testCreationTime(172832, 0, "1970-01-03 00:00:32.0");
  testCreationTime(0, 961549, "1970-01-01 00:00:00.961549");
  testCreationTime(0, 0, "1970-01-01 00:00:00.0");
}

void testNow() {
  cout << kINDENT << __PRETTY_FUNCTION__ << endl;

  struct timeval tval;
  gettimeofday(&tval, NULL);
  uint64_t usec = tval.tv_sec * 1e6 + tval.tv_usec;
  Time t1(tval);
  Time t2 = Time::usec(usec);

  usleep(1); // yes, c++ is that fast.
  Time now = Time::now();

  massert(t1 < now, "time1 should be less than time2");
  massert(t2 < now, "time1 should be less than time2");
  massert(t1 == t2, "time1 should be equal to time2");
  massert(now > t1, "time1 should be greater than time2");
  massert(now > t2, "time1 should be greater than time2");
  massert(t2 == t1, "time1 should be equal to time2");

}

void testArithmetic() {
  cout << kINDENT << __PRETTY_FUNCTION__ << endl;

  Time now = Time::now();
  Time us1 = Time::usec(1);
  Time now_p1 = now + us1;
  Time now_m1 = now - us1;

  massert(now < now_p1, "time1 should be less than time2");
  massert(now_m1 < now, "time1 should be less than time2");
  massert(now_m1 < now_p1, "time1 should be less than time2");

  massert(now > now_m1, "time1 should be greater than time2");
  massert(now_p1 > now, "time1 should be greater than time2");
  massert(now_p1 > now_m1, "time1 should be greater than time2");
}


int main(int argc, char **argv) {

  testCreation();
  testNow();
  testArithmetic();

  cout << endl << " Finished (" << errors << " errors)." << endl;

  return 0;
}