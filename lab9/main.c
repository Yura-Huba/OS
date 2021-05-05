#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(){
	pid_t pid, childpid;
	int status;
	if ((pid = fork()) == 0){
		execl("/bin/cat", "cat", "text.txt", NULL);
		printf("Error execl child proc\n");
		return -1;
			
	}else{
		if(pid<0){
			printf("Parent fork error\n");
			return -1;
		}
	}
	printf("Wait parent\n");
	
	childpid = waitpid(pid,&status,0);
	if(childpid==-1){
		printf("Error wait child\n");
		return -1;
	}
	
	printf("Parent: wait's return value: %ld\n", childpid);
	printf("Parent: pid parent %ld\n", getpid());
	printf("Parent: child's status: %d\n", WEXITSTATUS(status));
	return 0;
}
