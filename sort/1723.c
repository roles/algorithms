#include<stdio.h>
#include<stdlib.h>

/**
 *  原题：http://poj.org/problem?id=1723
 *  题意：N个士兵随机的分布在一些整数坐标点上，要将他们排成水平的一行，要求步数最少
 *  题意分析：先解决放到同一行的问题，对纵坐标进行排序，得：
 *            y1<=y2<=...<=y_mid...<=yn
 *            可以证明要使sum(yi-Y)最小，Y为中位数y_mid
 *
 *            简单证明
 *            *******************
 *            首先，给定一个从小到大的数列x1,x2,……，xn,
 *            设x是从x1到xn与其绝对差之和最小的数，则显然x位于x1与xn之间。
 *            那么，由于x1，xn与它们之间的任意一点的距离之和都相等，且都等于xn-x1，
 *            因此接下来可以不考虑x1与xn，而考虑剩下的从x2到x[n-1]的数，
 *            同样显然有x必然位于x2和x[n-1]之间，依次类推，最后得出的结论是
 *            x就是该数列中间的那个数，或者是中间的那两个数之一，而这个数就是中位数。
 *            *******************
 *            
 *            将所有点都放到同一行后，则要将其x坐标排成X,X+1,X+2.....X+n-1
 *            令x[i]=a[i]+i，即a[i]=x[i]-i，则当所有的a[i]都为X时，问题解决
 *            因此可以将问题转化为将所有的a[i]用最少步数归纳到X处，这就是上面所解决的问题
 *
 */

#define MAXN 10001

int cmp_int(const void *a, const void *b){
    return *((int*)a) - *((int*)b);
}

int main(){
    int N, i;
    int x[MAXN], y[MAXN], a[MAXN];
    int step;

    //freopen("input.txt", "r", stdin);
    scanf("%d", &N);

    for(i = 0; i < N; i++){
        scanf("%d%d", &x[i], &y[i]);
    }
    qsort(y, N, sizeof(int), cmp_int); 
    step = 0;
    for(i = 0; i < N; i++){
        if(i < (N-1) * 1.0 / 2){
            step -= y[i];      
        }else if(i > (N-1) * 1.0 / 2){
            step += y[i];
        }
    }
    qsort(x, N, sizeof(int), cmp_int);
    for(i = 0; i < N; i++){
        a[i] = x[i] - i;  
    }
    qsort(a, N, sizeof(int), cmp_int);
    for(i = 0; i < N; i++){
        if(i < (N-1) * 1.0 / 2){
            step -= a[i];      
        }else if(i > (N-1) * 1.0 / 2){
            step += a[i];
        }
    }
    printf("%d\n", step);
    return 0;
}

