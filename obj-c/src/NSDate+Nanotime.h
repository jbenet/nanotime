
#import <Foundation/Foundation.h>
#import "nanotime.h"


#ifndef __nanotime_typedef__
#define __nanotime_typedef__
typedef struct nanotime nanotime;
#endif


// WARNING: These conversions go through NSTimeInterval (float)
//          which will loose some precision (so far tested as high as 2 usec)
//
//          To bypass this lack of precision, don't use the NSDate category,
//          and instead use the C interface (in nanotime.h) directly.

@interface NSDate (Nanotime)
- (nanotime) nanotimeSince1970;
+ (NSDate *) dateWithNanotimeSince1970:(nanotime)ntime;

+ (nanotime) nanotimeWithTimeIntervalSince1970:(NSTimeInterval)interval;
+ (NSTimeInterval) timeIntervalWithNanotimeSince1970:(nanotime)ntime;
@end

