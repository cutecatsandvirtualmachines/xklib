EXTRA_CFLAGS = -I$(PWD)/include -Wno-incompatible-pointer-types -Wno-format -Wno-int-conversion
KBUILD_CFLAGS += -g -Wall
SRC_DIR := src
SRC := $(wildcard $(SRC_DIR)/*.c)
BIN := xklib.ko

obj-m += xklib.o
xklib-y := src/xklib.o src/memory.o src/cpu.o src/hashmap.o

all: clean test xklib

test:
	gcc -o runner/runner runner/runner.c -I ./include -Wno-format

xklib:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean