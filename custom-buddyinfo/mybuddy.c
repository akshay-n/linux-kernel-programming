#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h>

#define MOD_AUTHOR "Akshay Naik"
#define MOD_DESC "Module to implement custom /proc/buddyinfo"

static struct proc_dir_entry *mybud;

static int mybud_show(struct seq_file *m, void *v){
	struct pglist_data *pgl_dataptr;
	struct zone *zone_ptr;
	struct free_area *area;
	int i, j;

	seq_printf(m, "\n\tAkshay: my custom buddyinfo\n\n");
	pgl_dataptr = NODE_DATA(first_online_node);
		
	for (i = 0; i < MAX_NR_ZONES; i++){
		zone_ptr = &pgl_dataptr->node_zones[i];
		if(zone_ptr->present_pages){
		seq_printf(m, "Node 0, zone%9s", zone_ptr->name);
		for(j=0; j < MAX_ORDER; j++){
			area = &zone_ptr->free_area[j];
			seq_printf(m, "%7lu", area->nr_free);
			}
			seq_printf(m, "\n");
		}
	}
	return 0;
}

static int mybud_open(struct inode *inode, struct file *file){
	return single_open(file, mybud_show, NULL);
}

static const struct file_operations mybud_fops = {
	.owner	= THIS_MODULE,
	.open	= mybud_open,
	.read	= seq_read,
	.llseek	= seq_lseek,
	.release= single_release,
};

static int __init mybud_init(void){
	
	mybud = proc_create("mybuddy", 0, NULL, &mybud_fops);
	if(!mybud) return -ENOMEM;
	return 0;
}

static void __exit mybud_exit(void){
	remove_proc_entry("mybuddy", NULL);
}

module_init(mybud_init);
module_exit(mybud_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(MOD_AUTHOR);
MODULE_DESCRIPTION(MOD_DESC);
