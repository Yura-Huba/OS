#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
         close(fd);
         return 1;
     }

     displ[1] = 0L;
     while(read(fd,&c,1)){
         if( c == '\n' ) {
             j++;
             line_ln[i++] = j;
             displ[i] = lseek(fd, 0L, 1);
             j = 0;
         }
         else
             j++;
     }

     while( printf("Line number : ") && scanf("%d", &line_no)) {
         if(line_no <= 0)
             return 0;
         lseek(fd, displ[line_no], 0);
         if(read(fd, &buf, line_ln[line_no])){
             write(fdw, &buf, line_ln[line_no]);
         }
         else
             printf("Bad Line Number\n");
         }
         close(fd);
         close(fdw);
}
