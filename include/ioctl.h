#include "xstdint.h"

typedef union _xklib_ioctl_data {
	struct xklib_ioctl_init {
		xuint64_t vmcall_key;
	} init;
} xklib_ioctl_data, *pxklib_ioctl_data;

enum xklib_ioctl_code {
	xklib_init = _IOR(511, 1, xklib_ioctl_data *)
};