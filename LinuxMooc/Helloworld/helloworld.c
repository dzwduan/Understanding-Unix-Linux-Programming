#include<linux/init.h>  //init exit宏
#include<linux/kernel.h>
#include<linux/module.h>

//lvm_init 随意指定
static int __init lkm_init(void){
    //printk printf接口一样，但是printk可以指定消息的打印级别1~8
    printk("Hello World\n");
    return 0;
}


static void __exit lkm_exit(void){
    printk("Exit world\n");
}

module_init(lkm_init);
module_exit(lkm_exit);

MODULE_LICENSE("GPL");