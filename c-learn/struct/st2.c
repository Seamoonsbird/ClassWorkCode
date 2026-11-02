#include <stdio.h>
typedef struct sample{
    char m1;
    int m2;
    char m3;
}SAMPLE;
int main(void){
    SAMPLE s={'a',2,'b'};
    printf("size of SAMPLE: %zu\n",sizeof(SAMPLE));
    printf("m1: %c, address: %p\n",s.m1,(void*)&s.m1);
    printf("m2: %d, address: %p\n",s.m2,(void*)&s.m2);
    printf("m3: %c, address: %p\n",s.m3,(void*)&s.m3);
    return 0;
}