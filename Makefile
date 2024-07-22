obj-m += xklib.o

SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)

all: test xklib

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	gcc -o runner/runner runner/runner.c

xklib:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
