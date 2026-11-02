#include <stdio.h>
void move(int n,char a,char b,char c);
/*TODO:
假设n个盘需要fun（n）次，那么fun（n+1）=fun（n）+2n+1
操作即为将n的情况下的C换成B,B换成C，然后加一次从A到C的操作，然后将n的情况下的A换成B，A换成B；
可是这个换成应该怎样表示呢
奇数次就先放到C，偶数次就先放到B即可；
那我这样是不是应该用n和n-2的递归比较好
NO,n-2的递归是不可行的

后来受某种启发，可以将起始盘，过渡盘，终点盘直接传给函数
*/

int main(void){
    int n=0;
    printf("请输入一个整数：");
    scanf("%d",&n);
    if(n<1||n>10){
        printf("超出计算范围\n");
    }
    else {
        move(n,'A','B','C');
    }
    return 0;
}
void move(int n,char origin,char middle,char final){
    if (n==1){
        printf("Move disk from %c to %c\n",origin,final);
    }
    else {
        move(n-1,origin,final,middle);
        printf("Move disk from %c to %c\n",origin,final);
        move(n-1,middle,origin,final);
    }
}
