#include "xklib.h"

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("cutecatsandvirtualmachines");
MODULE_DESCRIPTION("~");

bool bXklibInit = false;

static int driver_open(struct inode *device_file, struct file *instance)
{
	return 0;
}

static int driver_close(struct inode *device_file, struct file *instance)
{
	return 0;
}

static int main_ioctl(struct file *file, unsigned int cmd,
		      xklib_ioctl_data *arg)
{
	xklib_ioctl_data kernel_data = { 0 };

	if (!access_ok(arg, sizeof(arg))) {
		dbg_msg("Supplied argument pointer is invalid: %p", arg);
		return EINVAL;
	}
	if (copy_from_user(&kernel_data, arg, sizeof(arg))) {
		dbg_msg("Failed copying IOCTL data!");
		return ENODATA;
	}

	switch (cmd) {
	case xklib_init: {
		dbg_msg("Passed vmcall key to init: 0x%llx",
			kernel_data.init.vmcall_key);
		break;
	}
	default: {
		dbg_msg("Could not find a valid command for: %d", cmd);
		break;
	}
	}
	return 0;
}

static struct file_operations fops = { .owner = THIS_MODULE,
				       .open = driver_open,
				       .release = driver_close,
				       .unlocked_ioctl = main_ioctl };

static int __init ModuleInit(void)
{
	if (bXklibInit) {
		dbg_msg("XKLib has already been initialized...?");
		return 0;
	}

	dbg_msg("XKLib initializing...");

	char *p = kmalloc(8, GFP_KERNEL);
	char *identity_base = p - virt_to_phys(p);
	dbg_msg("Current PAGE_OFFSET: 0x%llx", identity_base);
	xuint64_t i = 0;
	while (!*(size_t *)(identity_base + i)) {
		i += 8;
	}
	dbg_msg("data: 0x%llx", *(size_t *)(identity_base + i));
	kfree(p);

	int retval = register_chrdev(511, "/dev/dummy", &fops);
	if (retval == 0) {
		dbg_msg("ioctl_example - registered Device number Major: %d, Minor: %d",
			511, 0);
	} else if (retval > 0) {
		dbg_msg("ioctl_example - registered Device number Major: %d, Minor: %d",
			retval >> 20, retval & 0xfffff);
	} else {
		dbg_msg("Could not register device number!");
		return -1;
	}

	bXklibInit = true;

	return retval;
}

static void __exit ModuleExit(void)
{
	unregister_chrdev(511, "/dev/dummy");
	dbg_msg("XKLib exiting");
}

module_init(ModuleInit);
module_exit(ModuleExit);
