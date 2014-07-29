/*
 * 1860 Currency Exchange
 * 题意是求一个在不同货币的兑换后能够获益的环路
 * 
 * 解法：Bellman-Ford算法可以求最短路径问题时判断是否存在从源节点开始的负环路
 *       根据题意，将每一中货币看成一个节点，将最短路径问题转化为求最大兑换，
 *       起始的兑换值设为0（不同于最短路径的无穷大），而由于最大兑换路径可能出现重复节点，
 *       因此不能在|G.V|-1次循环解决，结束条件是没有边能松弛或者存在源节点的正环路
 */


#include <cstdio>

const int maxn = 10001;
const double eps = 10e-8;

struct edge {
    int begin, end;
    double rate, comm;
} edge[maxn];

double d[maxn];
int N, E, s;
double ori;

bool bellman_ford(){

    while(true){

        bool expand = false;
        for(int i = 0; i < 2*E; i++){
            if(d[edge[i].end] + eps < (d[edge[i].begin] - edge[i].comm) * edge[i].rate){
                d[edge[i].end] = (d[edge[i].begin] - edge[i].comm) * edge[i].rate;
                expand = true;
            }
        }

        if(d[s] > ori + eps)
            return true;

        if(!expand)
            break;
    }
    return false;
}

int main(){

    scanf("%d%d%d%lf",&N, &E, &s, &ori);
    s -= 1;

    for(int i = 0; i < E; i++){
        int a, b;
        scanf("%d%d", &a, &b);

        edge[2*i].begin = a - 1;
        edge[2*i].end = b - 1;
        scanf("%lf%lf", &edge[2*i].rate, &edge[2*i].comm);

        edge[2*i+1].begin = b - 1;
        edge[2*i+1].end = a - 1;
        scanf("%lf%lf", &edge[2*i+1].rate, &edge[2*i+1].comm);
    }

    for(int i = 0; i < N; i++){
        d[i] = 0; 
    }
    d[s] = ori;

    if(bellman_ford())
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
