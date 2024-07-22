#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

struct mystruct {
	int age;
	char* name;
};

int main() {
	int answer;
	struct mystruct test = {4, "Johannes"};
	int dev = open("/dev/dummy", O_WRONLY);
	if(dev == -1) {
		printf("Opening was not possible!\n");
		return -1;
	}

	printf("Opening was successfull!\n");

	char out[1] = {0};
	
	read(dev, out, 1);
	close(dev);
	return 0;
}