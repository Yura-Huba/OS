#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
     int fd,fdw;
     long displ[500]={0};
     int i = 1, j = 0, line_no, line_ln[500]={0};
     char c, buf[257];
     if(( fd =  open(argv[1], O_RDONLY)) == -1){
         printf("No find file- %s",argv[1]);
         return 1;
     }
     if(( fdw =  open(argv[2], O_CREAT|O_WRONLY)) == -1) {
         printf("No find file- %s",argv[2]);
         closeFile(&fd);
         return 1;
     }

     displ[1] = 0L;
     while(read(fd,&c,1)){
         if( c == '\n' ) {
             j++;
             line_ln[i++] = j;
             displ[i] = lseek(fd, 0L, 1);
             if(displ[i]==-1){
                printf("Error lseek");
                closeFile(&fd);
                closeFile(&fdw);
                return 0;
             }
             j = 0;
         }
         else
             j++;
     }

     while( printf("Line number : ") && scanf("%d", &line_no)) {
         if(line_no <= 0)
             return 0;
         lseek(fd, displ[line_no], 0);
         if(displ[line_no]==-1){
            printf("Error lseek");
            break;
         }
         if(read(fd, &buf, line_ln[line_no])){
             if(write(fdw, &buf, line_ln[line_no])==-1){
                printf("Error write");
                break;
             };
         }
         else
             printf("Bad Line Number\n");
         }
     closeFile(&fd);
     closeFile(&fdw);
}

