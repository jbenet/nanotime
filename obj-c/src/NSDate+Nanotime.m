
#import "NSDate+Nanotime.h"

#define kNANOSECONDS_PER_SECOND 1000000000L

@implementation NSDate (Nanotime)

- (nanotime) nanotimeSince1970 {
  NSTimeInterval interval = [self timeIntervalSince1970];
  return [[self class] nanotimeWithTimeIntervalSince1970:interval];
}

+ (NSDate *) dateWithNanotimeSince1970:(nanotime)ntime {
  NSTimeInterval interval = [self timeIntervalWithNanotimeSince1970:ntime];
  return [NSDate dateWithTimeIntervalSince1970:interval];
}


+ (nanotime) nanotimeWithTimeIntervalSince1970:(NSTimeInterval)interval {
  nanotime ntime;
  ntime.ns = (uint64_t) (interval * kNANOSECONDS_PER_SECOND);
  return ntime;
}

+ (NSTimeInterval) timeIntervalWithNanotimeSince1970:(nanotime)ntime {
  return (ntime.ns * 1.0) / (kNANOSECONDS_PER_SECOND);
}

@end

