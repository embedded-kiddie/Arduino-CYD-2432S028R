#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG true

#if     DEBUG
#include <stdio.h>
#include <assert.h>
#define DBG_EXEC(x)   x
#define DBG_ASSERT(x) assert(x)
#else
#define DBG_EXEC(x)
#define DBG_ASSERT(x)
#endif

#endif // _DEBUG_H_