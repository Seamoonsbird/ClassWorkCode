//删除操作
#include <stdio.h>
#include <stdlib.h>
struct link *AppendNode(struct link *head);
void DisplyNode(struct link *head);
void DeleteMemory(struct link *head);
struct link *DeleteNode(struct link *head,int nodeDate);
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
    printf("do you want to delete all nodes? (y/n):");
    scanf(" %c",&c);
    if(c=='y'||c=='Y'){
        printf("input the date of node you want to delete:");
        int nodeDate;
        scanf("%d",&nodeDate);
        head=DeleteNode(head,nodeDate);
        DisplyNode(head);
    }
    DeleteMemory(head);
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
void DeleteMemory(struct link *head){
    struct link *p=head;
    struct link *pr=NULL;
    while(p!=NULL){
        pr=p;
        p=p->next;
        free(pr);
    }
}
struct link *DeleteNode(struct link *head,int nodeDate){
    struct link *p=head;
    struct link *pr=NULL;
    if (head==NULL){
        printf("Linked Table is empty!\n");
        return (head);
    }
    while (nodeDate!=p->date && p->next!=NULL){
        pr=p;//为什么要用pr记录前一个节点？看下面pr->next=p->next;
        p=p->next;
    }
    if (nodeDate==p->date){
        if (p==head){
            head=p->next;
        }
        else {
            pr->next=p->next;
        }
        free(p);
    }
    else {
        printf("No such node!\n");
    }
    return (head);
}