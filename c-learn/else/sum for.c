#include<stdio.h>
int main()
{
    int n;
	double sum = 0.0;
    double sign=1.0;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    // Calculate sum from 1 to n
    for(int i = 1; i <= n; ++i)
    {
        sum += sign/i; 
    }

    printf("Sum = %f\n", sum);
    return 0;
}