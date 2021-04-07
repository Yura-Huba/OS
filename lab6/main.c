#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 257

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
     long displ[500];
     int fd1, fd2, i = 1, j = 0, line_no, line_ln[500];
     char c, buf[BUFSIZE];

     if ((fd1 = open("/dev/tty", O_RDONLY | O_NDELAY)) == -1) {
         printf("Error,open file console");
         return 1;
     }

     if ((fd2 = open(argv[1], O_RDONLY)) == -1) {
         printf("Error open -",argv[1]);
		 closeFile(&fd1);
         return 1;
         }

     displ[1] = 0L;
     while(read(fd2, &c, 1))
         if( c == '\n' ) {
             j++;
             line_ln[i++] = j;
             displ[i] = lseek(fd2, 0L, 1);
			 if(displ[i]==-1){
				 printf("Error lseek");
				 closeFile(&fd1);
				 closeFile(&fd2);
				 return 0;
			 {
             j = 0;
             }
         else
             j++;

     while(1){
         printf("you have 5 seconds to enter a line number\n");
         sleep(5);
         if ((i = read(fd1, buf, BUFSIZE)) == 0) {
             lseek(fd2, SEEK_SET, 0);
             while((i = read(fd2, buf, BUFSIZE)) > 0){
                 if(write(1, buf, i)==-1){
					 printf("Error write");
					 break;
				 }
			 }
			 closeFile(&fd1);
			 closeFile(&fd2);
             return 0;
         }
         else {
             buf[i] = '\0';
             line_no = atoi(buf);
             if(line_no <= 0)
                 return 0;
             lseek(fd2, displ[line_no], 0);
             if(read(fd2, buf, line_ln[line_no]))
                 write(1, buf, line_ln[line_no]);
             else
                 fprintf(stderr, "Bad Line Number\n");
         }
     }
	 closeFile(&fd1);
	 closeFile(&fd2);
	 return 0;
}
