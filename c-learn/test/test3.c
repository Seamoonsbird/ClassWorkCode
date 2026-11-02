/*在某度网盘中，当多个用户同时申请下载资源。系统需要根据用户的身份优先级进行调度：

普通用户（level = 1）

VIP用户（level = 2）

SVIP用户（level = 3）

下载任务采用“队列”模型管理。 默认情况下，“先申请先下载”； 
但如果有更高级别用户申请下载（级别排序为SVIP > VIP > 普通用户），
可以插队到优先级更低的用户前方，同等级的用户则按照默认情况排序。

请你完善下述算法，模拟如下操作：

Request：用户申请下载（入队）

示例： Request 用户名 level

Download：系统执行下载（出队）

示例：Download

Remove：删除队列中指定用户申请

示例：Remove 用户名

Display：遍历输出当前下载队列状态

示例：Display

Exit：退出当前程序

示例：Exit

其中，level取值：1（普通用户），2（VIP），3（SVIP） 入队规则：高等级用户应插入到低等级用户前面，同等级用户则按照先申请先下载原则。

// TODO 表示该部分的代码需要你根据描述的要求来完成。*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 用户节点定义
typedef struct Node {
    char name[50];
    int level; // 1=普通, 2=VIP, 3=SVIP
    struct Node* next;
} Node;

// 队列结构体
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// 初始化队列
// 参数：q-队列
void initQueue(Queue* q) 
{
    // TODO：完成队列初始化代码，队头用front,队尾用rear表示
    q->front = q->rear = NULL;
}

// 创建节点
Node* createNode(const char* name, int level) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->level = level;
    newNode->next = NULL;
    return newNode;
}

// Request操作：入队（带优先级插入）
// 参数：q-队列，name-用户名，level-等级
void request(Queue* q, const char* name, int level)
{
    Node* newNode = createNode(name, level);
    // 队列为空，直接加入
    if (q->front == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }
    // 插入逻辑：高等级插在低等级用户前面，同等级则排在后面
    // TODO：请按照该部分的要求补全代码
    if (level > q->front->level)
    {
        newNode->next = q->front;
        q->front = newNode;
        return;
    }
        Node* p=q->front;
        while (p->next != NULL && p->next->level >=level)
        {
            p = p->next;
        }
        if (p->next== NULL)
        {
            q->rear->next = newNode;
            q->rear = newNode;
        }
        if (p ->next!= NULL)
        {
            newNode->next = p->next;
            p->next = newNode;
        }
    
}
// Download操作：输出队首元素，并删除该元素
// 参数：q-队列
void download(Queue* q) {
    if (q->front == NULL) {
        printf("队列为空，没有可下载的任务。\n");
        return;
    }
    Node* temp = q->front;
    printf("下载中：%s (level=%d)\n", temp->name, temp->level);
    //TODO：继续完成删除队首元素的逻辑
    q->front = temp->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(temp);
}

void removeUser(Queue* q, const char* name) {
    if (q->front == NULL) {
        printf("队列为空，无法删除。\n");
        return;
    }
    Node* prev = NULL;
    Node* curr = q->front;
    while (curr != NULL && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("未找到用户：%s\n", name);
        return;
    }

    // 三种情况：头、尾、中间
    if (prev == NULL) {
        // 删除头
        q->front = curr->next;
        if (q->front == NULL) { // 原来只有一个节点
            q->rear = NULL;
        }
    }
    else {
        // 删除中间或尾
        prev->next = curr->next;
        if (curr == q->rear) { // 删除尾
            q->rear = prev;
        }
    }

    free(curr);
    printf("已删除用户：%s\n", name);
}


// Display操作：显示队列
// 参数：q-队列
void display(Queue* q) {
    if (q->front == NULL) {
        printf("当前队列为空。\n");
        return;
    }
    Node* curr = q->front;
    printf("当前下载队列：\n");
    while (curr != NULL) 
    {
        printf("用户名: %-10s | level: %d\n", curr->name, curr->level);
        // TODO：请完善剩余代码逻辑
        curr = curr->next;

    }
}

// 主函数：模拟操作命令
int main() 
{
    Queue q;
    initQueue(&q);

    char command[50];
    char name[50];
    int level;
    printf("=== 某度网盘下载调度系统 ===\n");
    printf("支持命令：Request 用户名 level | Download | Remove 用户名 | Display | Exit\n");
    printf("请输入命令：\n");
    while (scanf("%s", command) == 1)
    {
        
        if (strcmp(command, "Request") == 0)
        {
            if (scanf("%s %d", name, &level) != 2)
            {
                break;
            }
            // 完善用户等级判断逻辑，当出现无效用户等级时，输出：“无效的用户等级，请输入 1（普通） 2（VIP） 3（SVIP）。”，然后换行。
            // TODO：
            if (!(level == 1 || level == 2 || level == 3))
            {
                printf("无效的用户等级，请输入 1（普通） 2（VIP） 3（SVIP）。\n");
                continue;
            }
            request(&q, name, level);
            printf("用户 %s (level=%d) 已加入队列。\n", name, level);

        }
        else if (strcmp(command, "Download") == 0) {
            download(&q);

        }
        else if (strcmp(command, "Remove") == 0) {
            scanf("%s", name);
            removeUser(&q, name);

        }
        else if (strcmp(command, "Display") == 0) {
            display(&q);

        }
        else if (strcmp(command, "Exit") == 0) {
            printf("程序已退出。\n");
            break;
        }
        // 完善代码逻辑，当输入无效命令时，请输出“无效命令，请重新输入。”，然后换行
        // TODO：
        else
        {
            printf("无效命令，请重新输入。");
        }
    }

    return 0;
}