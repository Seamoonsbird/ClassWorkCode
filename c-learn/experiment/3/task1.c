/*请用C语言实现：铁路购票系统座位分配算法，用于处理一节车厢的座位分配。
规则如下：假设一节车厢有20排，每一排有5个座位，用A、B、C、D、F表示，
第一排就是1A、1B、1C、1E、1F，第二排就是2A、2B、2C、2D、2F，以此类推，
购票时，每次最多购买5张，座位分配策略师：
如果这几张票能安排在同一排相邻的座位，则安排在编号最小的相邻座位，
否则，安排在编号最小的几个空座位中（不考虑是否相邻）
*/

#include <stdio.h>
#define N 5
#define M 20
int main(void){
    int m;
    printf("请问你要买几次票\n");
    scanf("%d",&m);
    if (m>100){
        printf("票数不够\n");
        return 0;
    }
    int seat[M][N]={0};
    int i=0;//行
    int j=0;//列
    // seat[M][N]的含义：0=空座，1=已售出；i范围0~19（对应1~20排），j范围0~4（对应A/B/C/D/F）
    printf("请问你要分别买几张票\n");
    int n[100]={0};//这里刚开始用了n[N]，明显是不可以的，因为次数可以超过20
    for (i=0;i<m;i++){
        scanf("%d",n+i);
    }
    for (int k=0;k<m;k++){
        if (n[k]>5){
            printf("超出5张票不卖\n");
            return 0;
        }
    }
    int k=0;
    //这个for是为了遍历每一次买票
    for (k=0;k<m;k++){
        for(i=0;i<M;i++){
            j=0;
            while(seat[i][j]!=0){
                if(++j>N){
                    break;
                }
            }
            if(seat[i][j]==0&&j+n[k]<=N){
                //给每一次买票分配座位
                for(int l=0;l<n[k];l++){
                    seat[i][j]=1;
                    //改变作为是否售出的标志
                    //输出座位号
                    if(j!=4){
                        printf("%d%c",i+1,j+65);
                    }
                    else {
                        printf("%d%c",i+1,j+66);
                    }
                    if(l<n[k]-1){
                        printf(" ");
                    }
                    
                    j++;
                }
                break;
            }
            else{
                //本行无法满足要求，继续下一行寻找
                continue;
            }
            
        }
        if(i==M){
            //没有找到可以满足要求的行，分配最小的空座位
            int count=0;//记录已经分配的座位数
            for(int l=0;count<n[k];l++){
                int *p=&seat[0][0];
                if(*(p+l)==0){
                    if(l%5!=4){
                        printf("%d%c",l/5+1,l%5+65);
                    }
                    else {
                        printf("%d%c",l/5+1,l%5+66);
                    }
                    if(count<n[k]-1){
                        printf(" ");
                    }
                    *(p+l)=1;
                    count++;
                }
            }
        }
        printf("\n");
    }

    return 0;
}