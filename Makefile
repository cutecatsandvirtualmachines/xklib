obj-m += src/xklib.o

EXTRA_CFLAGS=-I$(PWD)/include -Wno-incompatible-pointer-types
SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)

all: test xklib

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	gcc -o runner/runner runner/runner.c -I ./include

xklib:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
