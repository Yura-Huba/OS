#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void fcloseFile(FILE *fd){
    if(fclose(fd)==-1){
        if(errno==EINTR){
            if(fclose(fd)==-1&&errno!=EINTR){;
                printf("Error fclose file");
            }
        }else{
            printf("Error fclose file");
        }
    }
}

int main(int argc, char **argv){
	FILE *fpin, *fpout;
	char line[BUFSIZ];
	char check=1;
	
	if ((fpin = fopen(argv[1], "r")) == (FILE *) NULL) {
		printf("Error popen wc");
		return -1;
	}
	
	if((fpout = popen("wc -l", "w"))== (FILE *) NULL){
		printf("Error popen wc");
		check=0;
	}
	if(check){
		while (fgets(line, BUFSIZ, fpin) != (char *)NULL)
			if (line[0] == '\n')
				if(fputs(line, fpout)==EOF){
					printf("Error fputs,EOF");
					break;
				}
	}
	
	fcloseFile(&fpin);
	if(check){
		if(pclose(fpout)==-1){
			printf("Error pclose");
		}
	}
}