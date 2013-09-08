#include<stdio.h>
#include<stdlib.h>

/**
 *  原题：http://poj.org/problem?id=1727
 *  题意：给定若干个点(t,x)，t表示时间维度，x表示空间维度，(t,x)表示一个事件发生在时间t位置x
 *        约定最大速度为1，即一个单位时间最多只能移动一个单位空间
 *        两个事件(t1,x1),(t2,x2)，如果t2 >= t1 + |x2 - x1|
 *        则事件(t1,x1)可以看成事件(t2,x2)的cause
 *        现在对于给定的所有点集(t,x)，限定其cause的个数为m
 *        求时间上最近的cause发生的时间t
 *  题意分析：根据题意可以看出对于点(x,y)，它的cause可以选过它作斜率为+1，-1的直线形成的下方三角区域
 *            要使一个时间y0满足多个点，则直线y=y0都要通过这些点所组成的下方三角区域
 *            有题意可以知道y0最小是-2000000，最大可能是所有点纵坐标的最小值ymin
 *            通过二分查找的方式在(-200000,ymin)之间不断的得到mid
 *            验证的方式是如果mid得到的cause > m，则说明y0在(l,mid-1)的区域之间
 *            如果cause <= m，则说明y0在(mid,r)之间
 *
 *            得到cause的方式是用贪心法求解 区域覆盖问题
 *            由于每个点(x,y)在直线y=mid上，过(x,y)用斜率为+1,-1的直线可以得到一个区域(l,r)
 *            这个区域上的点都可以作为(x,y)的cause，因此可以将问题转化为每个点对应一个区域
 *            求覆盖这些区域用到的最少点的数量
 *            贪心的解决方法是将这些区域按右边r从小到大排序，如果r相同则按l从大到小排序
 *            在第一个区域的r处放置点c1，遍历这些区域，如果当前区域的l>c，则在当前区域的r处再放置一个点c
 *            遍历完这些区域，则放置点的数量为最少的cause
 *
 *  细节：二分查找时更新边界l=mid 还是 l=mid+1是要根据题意的来决定的
 *        而每一次的mid更新是用(l+r)/2还是(l+r)/2+1则要结合l的选取及l+r的正负性来决定
 *        如果是l=mid,r=mid-1，则mid=(l+r)/2+1【l+r为正数的情况】，否则当最后只剩下两个元素时，
 *        mid总是取l，而l又取mid，在边界上出现死循环
 *        同时也要注意当l+r为负数的时候(l+r)/2会向右取，为了保持一致性，需要对l+r做正负判断
 */

#define MAXN 100001

struct point{
    int x, y;
} p[MAXN];

int n, m;

/**
 * @brief  这个排序其实已经实现了贪心法所需要的排序,(x+y)代表其右边界,(x-y)代表其左边界
 *         其实是过这点的两条直线在x轴上的截距
 */
int cmp_point(const void *a, const void *b){
    int ret;
    if((ret = ((struct point*)a)->x + ((struct point*)a)->y - (((struct point*)b)->x + ((struct point*)b)->y)) == 0){
        return ((struct point*)b)->x - ((struct point*)b)->y - (((struct point*)a)->x - ((struct point*)a)->y);
    }
    return ret;
}

int solve(int t){
    int l, r; 
    int i, x;
    int ret = 1;
   
    x = p[0].x + p[0].y - t;
    for(i = 1; i < n; i++){
        l = t - (p[i].y - p[i].x); 
        r = p[i].y + p[i].x - t;
        if(x < l){
            ret++;
            x = r;
        }
    }
    return ret;
}

int main(){
    int cases, icase;
    int i, j;
    int l, r, mid;
    int cause;

    //freopen("input.txt", "r", stdin);

    scanf("%d", &cases);
    icase = 0;
    while(cases--){
        icase++;
        scanf("%d%d", &n, &m);
        for(i = 0; i < n; i++){
            scanf("%d%d", &p[i].y, &p[i].x);   
        }
        qsort(p, n, sizeof(struct point), cmp_point);
        r = p[0].y;
        for(i = 1; i < n; i++){
            if(p[i].y < r){
                r = p[i].y;
            }
        }
        l = -2000000;
        while(l != r){
            mid = ((l + r) < 0) ? (l + r) / 2 : (l + r) / 2 + 1;
            cause = solve(mid);
            if(cause <= m){
                l = mid;
            }else{
                r = mid - 1;
            }
        }
        printf("Case %d: %d\n", icase, l);
    }
    return 0;
}
