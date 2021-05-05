#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>


int writeFile(int *fd,char buf[],int whence){
	if(write(*fd,buf,whence)==-1){
		if(errno==EINTR){
			if(write(*fd,buf,whence)==-1&&errno!=EINTR){
				printf("Error write");
				return 1;
			}
		}else{
			printf("Error write");
			return 1;
		}
	}
	return 0;
}

int writeConsole(char *buf,int whence){
	if(write(1,buf,whence)==-1){
		if(errno==EINTR){
			if(write(1,buf,whence)==-1&&errno!=EINTR){
				printf("Error write");
				return 1;
			}
		}else{
			printf("Error write");
			return 1;
		}
	}
	return 0;
}

void closeFile(int *fd){
    if(close(*fd)==-1){
        if(errno==EINTR){
            if(close(*fd)==-1&&errno!=EINTR){;
                printf("Error close file");
            }
        }else{
            printf("Error close file");
        }
    }
}

int readFile(int *fd,char *buf,int size_buf){
    int count;
	if((count=read(*fd,buf,size_buf))==-1){
		if(errno==EINTR){
			if((count=read(*fd,buf,size_buf))==-1&&errno!=EINTR){
				printf("Error read");
				return -1;
			}
		}else{
			printf("Error read");
			return -1;
		}
	}
	return count;
}

int main(int argc, char **argv){
	int pid;
	int fd[2];
	static char *lines[3] ={ "Here are 3 lines of text.\n",
	"I see you\n",
	"plz made to upper\n"
	};
	char input[1000];
	int i;
	int rtn;
	
	if (pipe(fd) == -1) {
		printf("Error pipe");
		return -1;
	}
	if ((pid = fork()) > 0) {
		closeFile(&fd[0]);
		for(i=0; i<3; i++)
			if(writeFile(&fd[1], lines[i], strlen(lines[i])))
				return -1;
		closeFile(&fd[1]);
	}
	else if (pid == 0) {
			closeFile(&fd[1]);
			while ((rtn=readFile(&fd[0], input, sizeof(input)))> 0) {
				for(i=0; i<rtn; i++)
					if(islower(input[i]))
						input[i] = toupper(input[i]);
			if(writeConsole(input, rtn)){
				break;
			}
			}
		closeFile(&fd[0]);
		return 1;
	}
	else{
		printf("Error fork,cannot fork");
		return -1;
	}
	return 0;
}