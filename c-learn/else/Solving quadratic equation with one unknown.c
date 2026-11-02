#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define EPS 1e-6
int main(){
    float a,b,c,p,q;
    //a=1;
    //b=2;
    //c=2;
    printf("请输入要解一元二次方程组的系数a,b,c:\n");
    scanf("%f %f %f",&a,&b,&c);
    if(fabs(a)<=EPS){
        printf("这不是一元二次方程组\n");
        exit(0);
    }
    float d=b*b-4*a*c;
    if(d>EPS){
        float x1=(-b+sqrt(d))/2*a;
        float x2=(-b-sqrt(d))/2*a;
        printf("方程有两个实数解%f和%f\n",x1,x2);
    }
    if (fabs(d)<=EPS){
        float x=-b/2*a;
        printf("方程有一个实数解%f\n",x);
    }
    else{
        float p=-b/2*a;
        float q=sqrt(fabs(d))/2*a;
        printf("方程有两个复数解%f+%fi和%f-%fi",p,q,p,q);
    }
    return 0;
}