#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<unistd.h>

void print_current_policy(pid_t pid){
	int policy = sched_getscheduler(pid);
	switch(policy){
		case SCHED_FIFO:
			printf("Current Policy : FIFO\n");
			break;
		case SCHED_RR:
			printf("Current Policy : Round Robin\n");
			break;
		case SCHED_OTHER:
			printf("Current Policy : SCHED_OTHER\n");
			break;
		default:
			printf("Current Policy : Unknown\n");
	}
}

int main(){
	pid_t pid = 0;
	struct sched_param param;

	// Print current scheduling policy
	print_current_policy(pid);
	
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	sched_setscheduler(pid, SCHED_FIFO, &param);
	printf("Scheduling policy is changed to SCHED_FIFO\n");
	
	// Print scheduling policy after changing to FIFO
	print_current_policy(pid);
	return 0;
}


