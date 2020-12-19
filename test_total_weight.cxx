#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid_dad = getpid();
	syscall(333);
	long set_weight = syscall(334, 0);
	pid_t pid1= fork();
	if (pid1 == 0){ // child
		long set_weight = syscall(334, 0);
		pid_t pid1_grandchild1= fork();
		if (pid1_grandchild1 == 0){ // child
			long set_weight = syscall(334, 6);
			//exit(0);
		} else {
			std::cout << "pid1_grandchild1= " << pid1_grandchild1 << std::endl;
			//exit(0);
		}
	} else{ // dad
		pid_t pid2= fork();
		if (pid2 ==0){ // child2
			long set_weight = syscall(334, 5);
				//exit(0);
			} else {

				std::cout << "pid dad " << getpid() << std::endl;
				std::cout << "pid1= " << pid1 << std::endl;
				std::cout << "pid2= " << pid2 << std::endl;
				
				//waitpid(pid1, NULL, WNOHANG);
			}
	}
	if (getpid() == pid_dad){
		sleep(5);
		long total_weight_final = syscall(335);
		std::cout << "total weight with children returned " << total_weight_final << std::endl;
		pid_t heaviest_child = syscall(336);
		std::cout << "heaviest_child is " << heaviest_child << std::endl;
	} else {
		sleep(10);
	}
	return 0;
}
