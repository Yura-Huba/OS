#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
const int N=10;
typedef struct node {
    char *s;
    struct node* next;
}node;

node* newNode(char *in)
{
     node *node1;
     node1 = malloc(sizeof(node));
     if(node1==NULL){
        return NULL;
     }
     node1->s = malloc(strlen(in) + 1);
     if(node1->s==NULL){
        return NULL;
     }
     strcpy(node1->s, in);
     node1->next = NULL;
     return(node1);
}
int main()
{
    char line[BUFSIZ];
    node *p;

    node *head = malloc(sizeof(node));
    head->next = NULL;
    node *here = head;
    if(head==NULL){
        printf("Memory error,no memory available");
        return 0;
    }
    printf("Enter the text\n");
    while (fgets(line,N,stdin) != NULL) {
        if (line[0] == '.')
            break;
        here->next = newNode(line);
        if(here->next==NULL){
            printf("Memory error,no memory available");
            here=head->next;
            while(here){
                free(head);
                head=here;
                here=head->next;
            }
            free(head);
            return 0;
        }
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
