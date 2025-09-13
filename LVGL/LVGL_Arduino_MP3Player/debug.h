//====================================================================
//
//====================================================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG   1

#if   (DEBUG == 2)
#include <stdio.h>
#include <assert.h>
#define DBG_EXEC(x)   x
#define DBG_ASSERT(x) assert(x)

#elif (DEBUG == 1)
#include <assert.h>
#define DBG_EXEC(x)
#define DBG_ASSERT(x) assert(x)

#else
#define DBG_EXEC(x)
#define DBG_ASSERT(x)
#endif

#endif // _DEBUG_H_