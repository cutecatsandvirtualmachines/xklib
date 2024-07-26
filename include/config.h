/*
* Enables debug options
*/
#define DEBUG_BUILD

/*
* When disabled all pseudorandom generations are treated as hardware generation
* requests
*/
#define ENABLE_PREDICTABLE_RANDOM

/*
* When disabled the function EPT::HideDriver will do nothing, use for debug only
*/
//#define ENABLE_EPT_PROTECTION

#ifndef DEBUG_BUILD

/*
* Enables DMA protection via IOMMU virtualization
*/
#define ENABLE_DMA_PROTECTION

#endif

#define RND_SECURE 1
#define RND_PSEUDO 0
#define RND_SECURITY_LEVEL RND_PSEUDO

#ifdef BUILD_SPOOFER
#ifdef DEBUG_BUILD
#define BUILD_FLAGS (0x0)
#else
#define BUILD_FLAGS (0x1)
#endif
#else
#ifdef DEBUG_BUILD
#define BUILD_FLAGS (0xff)
#else
#define BUILD_FLAGS (0x2)
#endif
#endif