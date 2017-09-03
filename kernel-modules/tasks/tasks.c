#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
#include <linux/sched.h>

static struct proc_dir_entry *tasks;

static int tasks_show(struct seq_file *m, void *v){
	struct list_head *pos;
	struct task_struct *p;
	struct tm tm1, tm2;
	struct timespec ts1, ts2;
	
	getboottime(&ts2);
	ts2.tv_sec = ts2.tv_sec - (sys_tz.tz_minuteswest*60);
	seq_printf(m, "\n\tAkshay: my custom ps\n\n");
	seq_printf(m, "UID\t PID\tPPID\tSTIME\t    TIME CMD\n");
	//list_for_each_safe(pos, q, init_task.tasks){
	list_for_each(pos, &init_task.tasks){
		p= list_entry(pos, struct task_struct, tasks);
		ts1 = ns_to_timespec(p->start_time);
  		time_to_tm(ts1.tv_sec, 0, &tm1);
  		time_to_tm(ts2.tv_sec, ts1.tv_sec, &tm2);
		//seq_printf(m, "comm:%s, pid:%d\n", tmp->comm, tmp->pid);
		if((p->parent->pid == 0) || (p->parent->pid == 2)){
		seq_printf(m, "%d\t%4d\t%4d\t%02d:%02d\t%02d:%02d:%02d [%s]\n", 
			p->real_cred->uid.val,
			p->pid,
			p->parent->pid,
			tm2.tm_hour,
			tm2.tm_min,
			tm1.tm_hour,
			tm1.tm_min,
			tm1.tm_sec,
			p->comm
			);
		}
		else seq_printf(m, "%d\t%4d\t%4d\t%02d:%02d\t%02d:%02d:%02d %s\n", 
			p->real_cred->uid.val,
			p->pid,
			p->parent->pid,
			tm2.tm_hour,
			tm2.tm_min,
			tm1.tm_hour,
			tm1.tm_min,
			tm1.tm_sec,
			p->comm
			);
	}
	
	return 0;
}

static int tasks_open(struct inode *inode, struct file *file){
	return single_open(file, tasks_show, NULL);
}

static const struct file_operations tasks_fops = {
	.owner	= THIS_MODULE,
	.open	= tasks_open,
	.read	= seq_read,
	.llseek	= seq_lseek,
	.release= single_release,
};

static int __init tasks_init(void){
	
	tasks = proc_create("tasks", 0, NULL, &tasks_fops);
	if(!tasks) return -ENOMEM;
	return 0;
}

static void __exit tasks_exit(void){
	remove_proc_entry("tasks", NULL);
}

module_init(tasks_init);
module_exit(tasks_exit);

MODULE_LICENSE("GPL");
