
ifneq	($(KERNELRELEASE),)
obj-m	:= dram.o 

else
KDIR	:= /lib/modules/5.8.0-49-generic/build
PWD	:= $(shell pwd)
default:	
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules 
	rm -r -f .tmp_versions *.mod.c .*.cmd *.o *.symvers 

endif

