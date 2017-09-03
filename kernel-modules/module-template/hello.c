#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define MOD_AUTHOR "Akshay Naik"
#define MOD_DESC "Hello World Module"

static int my_data __initdata = 99;

static char *name = "default_name";
static char *street = "default_street";
static char *city = "default_city";
static char *zip = "00000";

module_param(name, charp, 0000);
MODULE_PARM_DESC(name, "Name string");
module_param(street, charp, 0000);
MODULE_PARM_DESC(street, "Street string");
module_param(city, charp, 0000);
MODULE_PARM_DESC(city, "City string");
module_param(zip, charp, 0000);
MODULE_PARM_DESC(zip, "ZIP Code string");

static int __init hello_init(void){
printk(KERN_INFO "Loading hello module - Hello World %d\n", my_data);
printk(KERN_INFO "==============================================\n");
printk(KERN_INFO "Name : %s\n", name);
printk(KERN_INFO "Street : %s\n", street);
printk(KERN_INFO "City : %s\n", city);
printk(KERN_INFO "ZIP Code : %s\n",zip);
return 0;
}

static void __exit hello_exit(void){
printk(KERN_INFO "Exiting hello module - Goodbye World\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(MOD_AUTHOR);
MODULE_DESCRIPTION(MOD_DESC);