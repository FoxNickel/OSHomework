#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/moduleparam.h>
#include<linux/pid.h>

MODULE_LICENSE("GPL");
static int pid;
module_param(pid,int,0664);

static int show_info_init(void){
	struct task_struct *p,*psibling;
	struct list_head* pp;
	p = pid_task(find_vpid(pid),PIDTYPE_PID);//find process by pid
	printk(KERN_ALERT"P: %d %s",p->pid,p->comm);//show present process info
	/*show parent info*/
	if(p->real_parent==NULL){
		printk(KERN_ALERT"No Parent");
	}else{
		printk(KERN_ALERT"Parent :%d %s",p->real_parent->pid,p->real_parent->comm);
	}
	/*show sibling info*/
	list_for_each(pp,&p->real_parent->children){
		psibling = list_entry(pp,struct task_struct,sibling);
		printk(KERN_ALERT"sibling: %d %s",psibling->pid,psibling->comm);
	}
	/*show children info*/
	list_for_each(pp,&p->children){
		psibling = list_entry(pp,struct task_struct,sibling);
		printk(KERN_ALERT"children: %d %s",psibling->pid,psibling->comm);
	}
	return 0;
}

static void  show_info_exit(void){
	printk(KERN_ALERT"Exit show\n");
}

module_init(show_info_init);
module_exit(show_info_exit);
