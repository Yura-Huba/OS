#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>

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

int main(int argc, char *argv[]){
     char *displ[501];
     char *p, buf[10];
     int fd1, fd2, count, i = 1, j = 1, line_no, line_ln[500];
     off_t size;

     if ((fd1 = open("/dev/tty", O_RDONLY | O_NDELAY)) == -1) {
         printf("Error,file open console");
         return 0;
     }

     if ((fd2 = open(argv[1], O_RDONLY)) == -1) {
         printf("File open error,name %s",argv[1]);
		 closeFile(&fd1);
         return 0;
         }

     size = lseek(fd2, 0, SEEK_END);
     if((p = mmap(0, size, PROT_READ, MAP_SHARED, fd2, 0))==MAP_FAILED){
		 printf("Error mmap");
		 closeFile(&fd1);
		 closeFile(&fd2);
		 return 0;
	 }

     displ[1] = p;
     for(count = 0; count < size; count++)
         if( *(p+count) == '\n' ) {
             line_ln[i++] = j;
             displ[i] = count+p+1;
             j = 1;
             }
         else
             j++;

     displ[i] = 0;
     while(1){
         printf("you have 5 seconds to enter a line number\n");
         sleep(5);
         if ((i = read(fd1, buf, 10)) == 0) {
             if(write(1, p, size)==-1){
				 printf("Fail write");
			 }
             break;
         }
         else {
             buf[i] = '\0';
             line_no = atoi(buf);
             if(line_no <= 0){
                 break;
			 }
             if(displ[line_no] != 0)
                 if(write(1, displ[line_no], line_ln[line_no])==-1){
					 printf("Fail write");
					 break;
				 }
             else
                 fprintf(stderr, "Bad Line Number\n");
         }
     }
	 closeFile(&fd1);
	 closeFile(&fd2);
}