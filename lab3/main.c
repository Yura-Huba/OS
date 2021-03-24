#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *file;
	uid_t uid;
     if(argc <2){
         fprintf("argc <2");
         return 1;
     }
     printf("initially uid=%ld and euid=%ld\n", getuid(), geteuid());
     if((file = fopen(argv[1], "r")) == NULL) {
         perror(argv[0]);
         return 2;
     }
     else{
         printf("first open successful\n");
         fclose(file);
     }
     setuid( uid=getuid() );
     printf("after setuid(%ld):\n   uid=%ld and euid=%ld\n",uid, getuid(), geteuid() );
     if((file = fopen(argv[1], "r")) == NULL) {
         perror(argv[0]);
		 return 3;
     }
     else{
         printf("second open successful\n");
         fclose(file);
     }
}