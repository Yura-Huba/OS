#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[]){
	int status;
	pid_t pid;
	if ((pid = fork()) == 0) {
		if(execvp(argv[1], &argv[1])==-1){
			perror(argv[1]);
			return -1;
		}
	}else{
		if(pid<0){
			printf("Parent fork error\n");
			return -1;
		}
	}
	printf("Parent wait child\n");
	if(wait(&status)==-1){
		printf("Parent wait error\n");
	}
	
	printf("Parent: child status: %d\n", WEXITSTATUS(status));
	return 0;
}