/*
 * 2201 Cartesian Tree
 * 笛卡尔树的构建
 * 要点：先将所有的node按k排序乘一个序列，然后以a为键构建笛卡尔树
 *       从左往右访问序列，当前要插入的值为x，从x所在的前一个位置开始
 *       回溯到树的根，直到找到一个节点y，满足y<x，
 *       则y作为x的父节点，x作为y的右节点，原来y的右节点作为x的左节点
 *       如果遍历到根节点仍不满足，则原来的根y作为x的左节点，x作为根
 *
 */


#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define MAXNODE 50005

struct node {
    int a, k;
    int idx;
};

node T[MAXNODE];
int par[MAXNODE], lc[MAXNODE], rc[MAXNODE];
int pos[MAXNODE];

int cmp_node_by_k(const void *pa, const void *pb){
    node* a = (node*)pa;
    node* b = (node*)pb;

    if(a->k < b->k){
        return -1;
    }else{
        return 1;
    }
}

void build_cartesian_tree(int N){
    for(int i = 1; i < N; i++){
        int j;
        for(j = i-1; T[i].a < T[j].a && par[T[j].idx] != 0; j = pos[par[T[j].idx]]);
        
        if(T[i].a < T[j].a){        //root
            par[T[j].idx] = T[i].idx;
            lc[T[i].idx] = T[j].idx;
        }else{
            par[T[i].idx] = T[j].idx;
            par[rc[T[j].idx]] = T[i].idx;
            lc[T[i].idx] = rc[T[j].idx];
            rc[T[j].idx] = T[i].idx;
        }

    }
}

int main(){
    int N;

    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d%d", &T[i].k, &T[i].a);
        T[i].idx = i+1;
        par[i+1] = lc[i+1] = rc[i+1] = 0;
    }

    qsort(T, N, sizeof(node), cmp_node_by_k);

    for(int i = 0; i < N; i++)
        pos[T[i].idx] = i;

    build_cartesian_tree(N);

    cout << "YES" << endl;
    for(int i = 1; i <= N; i++){
        cout << par[i] << " " << lc[i] << " " << rc[i] << endl;
    }

    return 0;
}
