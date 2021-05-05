#include <stdio.h>
int main(int argc, char **argv){
	int fptr;
	char *lines[3] ={ "Here are 3 lines of text.\n",
	"I see you\n",
	"plz,made to upper,azzaazaz\n"
	};
	
	if((fptr = popen("File", "w"))<=0){
		printf("Error popen");
		return -1;
	}

	for(int i=0; i<3; i++)
		if(fputs(lines[i], fptr)==EOF){
			printf("Error fputs,EOF");
			break;
		}
			
	
	int status=pclose(fptr);
	int status1;
	if(WIFEXITED(status)){
		printf("Error pclose");
	}else{
		status1=WEXITSTATUS(status);
		//
	}
	
	return 0;
}