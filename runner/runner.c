#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "ioctl.h"

int main() {
	int dev = open("/dev/dummy", O_RDWR);
	if(dev == -1) {
		printf("Opening was not possible!\n");
		return -1;
	}

	printf("Opening was successfull!\n");

	xklib_ioctl_data data = {0};
	data.init.vmcall_key = 0xdeadbeef;

	printf("Calling with IOCTL: 0x%llx\n", xklib_init);
	printf("IOCTL result: %d\n", ioctl(dev, xklib_init, &data));
	printf("Last error: %d\n", errno);
	
	close(dev);
	return 0;
}