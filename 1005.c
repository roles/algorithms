#include<stdio.h>

#define pi 3.141592657

int main(){
    int N, i, z;
    double x, y;

    scanf("%d", &N);
    i = 0;
    while(++i <= N){
        scanf("%lf%lf", &x, &y);
        z = (int)(pi * (x * x + y * y) / 100) + 1;
        printf("Property %d: This property will begin eroding in year %d.\n", i, z);
    }
    printf("END OF OUTPUT.");
    return 0;
}
