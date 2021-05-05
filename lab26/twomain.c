#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

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

int main(){
	char input[1000];
	int i;
	int rtn;
	
	while ((rtn=readFile(0, input, 1000))> 0) {
	for(i=0; i<rtn; i++)
		if(islower(input[i]))
			input[i] = toupper(input[i]);
		if(writeConsole(input, rtn)){
			break;
		}
	}
	return 0;
}
