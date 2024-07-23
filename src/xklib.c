#include "xklib.h"

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("cutecatsandvirtualmachines");
MODULE_DESCRIPTION("~");

bool bXklibInit = false;

static int driver_open(struct inode *device_file, struct file *instance) {
	return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
	return 0;
}

static int main_ioctl(struct file *file, unsigned int cmd, xklib_ioctl_data* arg) {
	xklib_ioctl_data kernel_data = {0};

	if(!access_ok(arg, sizeof(arg))) {
		printk("Supplied argument pointer is invalid: %p", arg);
		return EINVAL;
	}
	if(copy_from_user(&kernel_data, arg, sizeof(arg))) {
		printk("Failed copying IOCTL data!\n");
		return ENODATA;
	}

	switch(cmd) {
		case xklib_init: {
			printk("Passed vmcall key to init: 0x%llx\n", kernel_data.init.vmcall_key);
			break;
		}
		default: {
			printk("Could not find a valid command for: %d\n", cmd);
			break;
		}
	}
        return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.unlocked_ioctl = main_ioctl
};

static int __init ModuleInit(void) {
	if(bXklibInit) {
		printk("XKLib has already been initialized...?\n");
		return 0;
	}

	printk("XKLib initializing...\n");

	int retval = register_chrdev(511, "/dev/dummy", &fops);
	if(retval == 0) {
		printk("ioctl_example - registered Device number Major: %d, Minor: %d\n", 511, 0);
	}
	else if(retval > 0) {
		printk("ioctl_example - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	}
	else {
		printk("Could not register device number!\n");
		return -1;
	}

	bXklibInit = true;

	return retval;
}

static void __exit ModuleExit(void) {
	unregister_chrdev(511, "/dev/dummy");
	printk("XKLib exiting\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
