//================================================================================
// Defining debugging functions
//================================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG   0

#if (DEBUG == 0)
#define DBG_EXEC(x)
#define DBG_ASSERT(x)
#endif

#if (DEBUG & 1)
#include <stdio.h>
#define DBG_EXEC(x)   x
#endif

#if (DEBUG & 2)
#include <assert.h>
#define DBG_ASSERT(x) assert(x)
#endif

#endif // _DEBUG_H_