#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#include "ioctl.h"
#include "debug.h"
#include "memory.h"
#include "status.h"

#define DEVICE_NAME "xklib"
#define CLASS_NAME "XKClass"