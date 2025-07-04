#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG true

#if     DEBUG
#define DBG_EXEC(x) x
#else
#define DBG_EXEC(x)
#endif

#endif // _DEBUG_H_