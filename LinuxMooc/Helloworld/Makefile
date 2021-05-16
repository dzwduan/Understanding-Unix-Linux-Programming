obj-m:=helloworld.o  #最后生成对应的helloworld.ko

#增强移植性
CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL:=$(shell uname -r)
LINUX_KERNEL_PATH:=/usr/src/linux-headers-5.8.0-49-generic

#-C make路径 -M指定编译完放在哪个目录 modules表明编译的是内核模块
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
