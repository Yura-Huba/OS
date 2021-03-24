#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct node {
    char *s;
    struct node* next;
}node;

node* new(char *in)
{
     node *node1;
     node1 = malloc(sizeof(node));
     node1->s = malloc(strlen(in) + 1);
     strcpy(node1->s, in);
     node1->next = NULL;
     return(node1);
}
int main()
{
    char line[BUFSIZ];
    node *p, *new(char *);
	
    node *head = malloc(sizeof(node));
    head->next = NULL;
    node *here = head;
	
    printf("Enter the text\n");
    while (gets(line) != NULL) {
        if (line[0] == '.')
            break;
        here->next = new(line);
        here = here->next;
    }
	node* t=NULL;
    for (p = head->next; p != NULL; p = p->next){
		if(t!=NULL){
			free(t->s);
			free(t);
		}
        puts(p->s);
		t=p;
	}
}