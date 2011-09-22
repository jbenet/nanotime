
import time
import datetime
import unittest
import nanotime

class TestTime(unittest.TestCase):

  def test_construction(self):

    def eq(time1, time2):
      self.assertEqual(time1, time2)
      self.assertEqual(int(time1), time2._ns)
      self.assertEqual(time1._ns, int(time1))
      self.assertEqual(time1._ns, int(time2))
      self.assertEqual(time1._ns, time2._ns)
      self.assertEqual(time1.nanoseconds(), time2.nanoseconds())
      self.assertEqual(time1.microseconds(), time2.microseconds())
      self.assertEqual(time1.milliseconds(), time2.milliseconds())
      self.assertEqual(time1.seconds(), time2.seconds())
      self.assertEqual(time1.minutes(), time2.minutes())
      self.assertEqual(time1.hours(), time2.hours())
      self.assertEqual(time1.days(), time2.days())
      self.assertEqual(time1.timestamp(), time2.timestamp())
      self.assertEqual(time1.datetime(), time2.datetime())
      self.assertEqual(time1.unixtime(), time2.unixtime())

      #self.assertEqual(time1, time1.unixtime())
      #self.assertEqual(time1, time2.unixtime())
      #self.assertEqual(time1, time1.timestamp())
      #self.assertEqual(time1, time2.timestamp())

      #self.assertEqual(time2, time1.unixtime())
      #self.assertEqual(time2, time2.unixtime())
      #self.assertEqual(time2, time1.timestamp())
      #self.assertEqual(time2, time2.timestamp())

    def close(x, y, epsilon=1e-6):
        return abs(x - y) < epsilon

    for i in range(0, 50):
      # basic
      eq(nanotime.seconds(1), nanotime.nanoseconds(1e9))
      eq(nanotime.seconds(1), nanotime.microseconds(1e6))
      eq(nanotime.seconds(1), nanotime.milliseconds(1e3))
      eq(nanotime.seconds(1), nanotime.seconds(1))
      eq(nanotime.seconds(1), nanotime.minutes(1.0/60))
      eq(nanotime.seconds(1), nanotime.hours(1.0/3600))
      eq(nanotime.seconds(1), nanotime.days(1.0/(3600 * 24)))

      nt1 = nanotime.now()
      self.assertTrue(nanotime.now() > nt1)

      # timestamp
      ts1 = time.time()
      ts2 = nanotime.timestamp(ts1).timestamp()
      eq(nanotime.timestamp(ts1), nanotime.timestamp(ts1))
      self.assertTrue(close(ts2, ts1))
      self.assertEqual(nanotime.timestamp(ts1), ts1)

      # datetime
      dt1 = datetime.datetime.now()
      dt2 = nanotime.datetime(dt1).datetime()
      eq(nanotime.datetime(dt1), nanotime.datetime(dt1))
      self.assertTrue(close(dt1, dt2, datetime.timedelta(microseconds=1)))
      # self.assertTrue(cmp(dt1, dt2) == cmp(nanotime.datetime(dt1), dt1))
      # FIXME(jbenet)
      # cmp() raises: TypeError: can't compare datetime.datetime to nanotime

  def __subtest_arithmetic(self, start, extra):
    eq = self.assertEqual

    start = float(start)
    extra = float(extra)
    t1 = nanotime.seconds(start)
    eq(nanotime.seconds(start + extra), t1 + nanotime.nanotime(extra * 1e9))
    eq(nanotime.seconds(start + extra), t1 + nanotime.seconds(extra))
    eq(nanotime.seconds(start - extra), t1 - nanotime.nanotime(extra * 1e9))
    eq(nanotime.seconds(start - extra), t1 - nanotime.seconds(extra))
    eq(nanotime.seconds(start * extra), t1 * nanotime.nanotime(extra))
    eq(nanotime.seconds(start * extra), t1 * nanotime.nanoseconds(extra))
    eq(nanotime.seconds(start / extra), t1 / nanotime.nanotime(extra))
    eq(nanotime.seconds(start / extra), t1 / nanotime.nanoseconds(extra))

    self.assertTrue(nanotime.seconds(start + extra) > t1)
    self.assertTrue(nanotime.seconds(start - extra) < t1)

    t2 = nanotime.seconds(start + extra)
    self.assertTrue(t2  > nanotime.nanotime(0))
    self.assertTrue(nanotime.nanotime(0) < t2)

  def test_arithmetic(self):
    for start in range(0, 10000, 1000):
      for extra in range(1, 20, 5):
        self.__subtest_arithmetic(start, extra)


