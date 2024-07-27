#include "xklib.h"

bool bXklibInit = false;

static int __init ModuleInit(void)
{
	if (bXklibInit) {
		dbg_msg("XKLib has already been initialized...?");
		return 0;
	}

	dbg_msg("XKLib initializing...");

	xklib_error err = mm_init();

	bXklibInit = true;

	return err;
}

static void __exit ModuleExit(void)
{
	mm_destroy();

	dbg_msg("XKLib exiting");
}

module_init(ModuleInit);
module_exit(ModuleExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("cutecatsandvirtualmachines");
MODULE_DESCRIPTION("~");