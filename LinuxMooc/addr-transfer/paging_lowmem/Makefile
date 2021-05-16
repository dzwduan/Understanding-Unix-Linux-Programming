obj-m:=paging_lowmem.o

PWD:=$(shell pwd)
KERNELDIR:=/lib/modules/5.8.0-49-generic/build

all:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	@rm -rf *.o *.mod.o *.ko *.order *.symvers .*.cmd .tmp_versions