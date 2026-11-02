//加入可插入数据功能,假设已经升序排序
#include <stdio.h>
#include <stdlib.h>
struct link *AppendNode(struct link *head);
void DisplyNode(struct link *head);
void DeleteMemory(struct link *head);
struct link *DeleteNode(struct link *head,int nodeData);
struct link *InsertNode(struct link *head,int nodeData);

struct link{
    int data;
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
    printf("do you want to delete a nodes? (y/n):");
    scanf(" %c",&c);
    if(c=='y'||c=='Y'){
        printf("input the data of node you want to delete:");
        int nodeData;
        scanf("%d",&nodeData);
        head=DeleteNode(head,nodeData);
        DisplyNode(head);
    }
    printf("do you want to insert a new node? (y/n):");
    scanf(" %c",&c);
    if (c=='y'||c=='Y'){
        printf("input the data of node you want to insert:");
        int nodeData;
        scanf("%d",&nodeData);
        head=InsertNode(head,nodeData);
        DisplyNode(head);
    }
    DeleteMemory(head);
    return 0;
}


struct link *AppendNode(struct link *head){
    struct link *pr=head;
    struct link *p=NULL;
    int data;
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
    printf("input node data:");
    scanf("%d",&data);
    p->data=data;
    p->next=NULL;
    return head;
}
void DisplyNode(struct link *head){
    struct link *p=head;
    int j=1;
    while(p!=NULL){
        printf("%5d%10d\n",j,p->data);
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
struct link *DeleteNode(struct link *head,int nodeData){
    struct link *p=head;
    struct link *pr=NULL;
    if (head==NULL){
        printf("Linked Table is empty!\n");
        return (head);
    }
    while (nodeData!=p->data && p->next!=NULL){
        pr=p;
        p=p->next;
    }
    if (nodeData==p->data){
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

struct link *InsertNode(struct link *head,int nodeData){
    struct link *p=NULL;
    struct link *pr=head;
    struct link *temp=NULL;
    p=(struct link *)malloc(sizeof(struct link));
    if (p==NULL){
        printf("memory allocation failed!\n");
        exit(0);
    }
    p->next=NULL;
    p->data=nodeData;
    if (head==NULL){
        head=p;
    }
    else{
        while (pr->next!=NULL && pr->data<nodeData){
            temp=pr;
            pr=pr->next;
        }
        if (pr->data>=nodeData){
            if(pr==head){
                p->next=head;
                head=p;
            }
            else {
                pr=temp;//上面已经让pr往后走了，这里要让pr回到temp位置
                p->next=pr->next;
                pr->next=p;

            }
        }
        else{
            pr->next=p;
        }
    }
    return head;
}