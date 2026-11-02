//建立单向链表,并在最后新建一个节点
#include <stdio.h>
#include <stdlib.h>
struct link *AppendNode(struct link *head);
void DisplyNode(struct link *head);
void DeleteNode(struct link *head);
struct link{
    int date;
    struct link *next;
};
int main(void){
    int i=0;
    char c;
    struct link *head=NULL;
    printf("do you want to append a new node? (y/n):");
    scanf(" %c",&c);
    while(c=='y'||c=='Y'){
        head=AppendNode(head);
        DisplyNode(head);
        printf("do you want to append a new node? (y/n):");
        scanf(" %c",&c);
        i++;
    }
    printf("%d new nodes have been appended\n",i);
    DeleteNode(head);
    return 0;
}
struct link *AppendNode(struct link *head){
    struct link *pr=head;
    struct link *p=NULL;
    int date;
    p=(struct link *)malloc(sizeof(struct link));
    if(p==NULL){
        printf("memory allocation failed!\n");
        exit(0);
    }
    if(head==NULL){
        head=p;
    }else{
        while(pr->next!=NULL){
            pr=pr->next;
        }
        pr->next=p;
    }
    printf("input node date:");
    scanf("%d",&date);
    p->date=date;
    p->next=NULL;
    return head;
}
void DisplyNode(struct link *head){
    struct link *p=head;
    int j=1;
    while(p!=NULL){
        printf("%5d%10d\n",j,p->date);
        p=p->next;
        j++;
    }
}
void DeleteNode(struct link *head){
    struct link *p=head;
    struct link *pr=NULL;
    while(p!=NULL){
        pr=p;
        p=p->next;
        free(pr);
    }
}