#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/list.h>

asmlinkage long sys_hello(void) {
	printk("Hello, World!\n");
	return 0;
}

asmlinkage long sys_set_weight(int weight) {
	if (weight < 0){
		return -EINVAL;
	}
	current->weight = weight;
	return 0;
}

static int _get_total_weight_recursive(struct task_struct * task){
	struct list_head *p;
	struct task_struct *child;
	int sum = task->weight;
	list_for_each(p, &task->children){
		child = list_entry(p, struct task_struct, sibling);
		sum += _get_total_weight_recursive(child);
	}
	return sum;
}

asmlinkage long sys_get_total_weight(void){
	return _get_total_weight_recursive(current);
}

asmlinkage long sys_get_heaviest_child(void){
	struct list_head *p;
	struct task_struct *ts;
	int max = -1;
	pid_t max_pid;
	list_for_each(p, &(current->children)){
		ts = list_entry(p, struct task_struct, sibling);
		int current_weight = _get_total_weight_recursive(ts);
		if (current_weight > max){
			max = current_weight;
			max_pid = ts->pid;
		}
	}
	
	if (max == -1){
		return -ECHILD;
	}
	
	return max_pid;
}




