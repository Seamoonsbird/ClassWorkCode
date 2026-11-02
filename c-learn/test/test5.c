#include <stdio.h>
double fn(double x,int n);
int main(){
    int n;
    double x;
    scanf("%lf %d",&x,&n);
    printf("%f",fn(x,n));
    return 0;
}

double fn(double x,int n){
    if(n>1){
        return x-x*fn(x,n-1);
    }
    else {
        return x;
    }
}