#include "config.h"

#ifdef DEBUG_BUILD
#ifndef ENABLE_EPT_PROTECTION

#define dbg_msg(x, ...) printk(x "\n", ## __VA_ARGS__)

#else

#define dbg_msg(x, ...) 

#endif
#else 

#define dbg_msg(x, ...)

#endif