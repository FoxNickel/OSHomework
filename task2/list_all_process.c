#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>

static int list_all_process_init(void)
{
	struct task_struct *p;
	p = NULL;
	printk(KERN_ALERT"name\tpid\tstate\tprio\t");
	for_each_process(p)
	{
		printk(KERN_NOTICE"%s\t%d\t%ld\t%d\t",p->comm,p->pid,p->state,p->normal_prio);
	}
	return 0;
}

static void list_all_process_exit(void)
{
	printk(KERN_NOTICE"Exit\n");
}
module_init(list_all_process_init);
module_exit(list_all_process_exit);
MODULE_LICENSE("GPL");
