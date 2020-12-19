#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	syscall(333);
	pid_t pid = getpid();
	long set_weight = syscall(334, 1);
	fork();
	fork();
	fork();
	fork();
	std::cout << " my pid is: "<< getpid()<< std::endl;

	if (getpid() == pid){  // run it only for dad
		sleep(5);
		long total_weight_final = syscall(335);
		std::cout << "total weight is: " << total_weight_final << " my pid is: "<< getpid()<< std::endl;
		//wait(NULL);
		//wait(NULL);
		//wait(NULL);
	} else {
	sleep(10);
	}

	return 0;
}
