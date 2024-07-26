obj-m += xklib.o
xklib-y := src/xklib.o src/memory.o

EXTRA_CFLAGS=-I$(PWD)/include -Wno-incompatible-pointer-types -Wno-format
SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)

all: test xklib

test:
	gcc -o runner/runner runner/runner.c -I ./include -Wno-format

xklib:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean