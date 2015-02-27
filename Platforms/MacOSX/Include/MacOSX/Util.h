#import <Foundation/Foundation.h>

extern BOOL shouldTerminate;

#if defined __cplusplus
extern "C" {
#endif

void requestTermination();

#if defined __cplusplus
};
#endif
