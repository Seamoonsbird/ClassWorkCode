#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("请输入你要计算的算式子:\n");
    int result,num_1,middleResult;
    char sign;
    scanf("%d%c",&result,&sign);
    do{
        scanf("%d",&num_1);

        if (sign=='+')
            middleResult=result+num_1;
        else if(sign=='-')
            middleResult=result-num_1;
        else if(sign=='*')
            middleResult=result*num_1;
        else if(sign=='/')
            middleResult=result/num_1;
        else{
            printf("错误的运算符:%c\n",sign);
            return 0;
        }
        result=middleResult;
        scanf("%c",&sign);
    }while (sign!='=');
    printf("%d\n",result);
    return 0;
}