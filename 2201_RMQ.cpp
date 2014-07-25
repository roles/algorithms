/*
 * 笛卡尔树，用RMQ的方法去解，在POJ上RE
 *
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAXVAL 30000

struct node {
    int a, k;
    int idx;
    int p, lc, rc;
};

static node T[50001];
static int a2pos[MAXVAL*2+1];
static int rmq[50001][17];

int cmp_node_by_k(const void *pa, const void *pb){
    node* a = (node*)pa;
    node* b = (node*)pb;

    if(a->k < b->k){
        return -1;
    }else{
        return 1;
    }
}

int cmp_node_by_idx(const void *pa, const void *pb){
    node* a = (node*)pa;
    node* b = (node*)pb;

    if(a->idx < b->idx){
        return -1;
    }else{
        return 1;
    }
}

int query_rmq(int b, int e){
    int lg = (int)(log(1.0 * (e-b+1)) / log(2.0));
    return min(rmq[b][lg], rmq[e-(1<<lg)+1][lg]);
}

int build_tree(int b, int e, int root){
    if(b == e){
        T[b].p = root;
        T[b].lc = 0;
        T[b].rc = 0;
        return b;
    }
    int min_val = query_rmq(b, e);
    int min_idx = a2pos[min_val];
    T[min_idx].p = root;

    int lc_idx, rc_idx;
    if(b != min_idx){
        lc_idx = build_tree(b, min_idx-1, T[min_idx].idx); 
        T[min_idx].lc = T[lc_idx].idx;
    }else{
        T[min_idx].lc = 0;
    }

    if(e != min_idx){
        rc_idx = build_tree(min_idx+1, e, T[min_idx].idx);
        T[min_idx].rc = T[rc_idx].idx;
    }else{
        T[min_idx].rc = 0;
    }

    return min_idx;
}

int main(){
    int N;

    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d%d", &T[i].k, &T[i].a);
        T[i].idx = i+1;
        T[i].p = T[i].lc = T[i].rc = 0;
    }

    qsort(T, N, sizeof(node), cmp_node_by_k);
    
    for(int i = 0; i < N; i++){
        rmq[i][0] = T[i].a;
        a2pos[T[i].a] = i;
    }
    
    int lg = (int)(log(N * 1.0) / log(2.0));
    
    for(int j = 1; j <= lg; j++){
        for(int i = 0; i <= N - (1<<j); i++){
            rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
        }
    }

    build_tree(0, N-1, 0);

    qsort(T, N, sizeof(node), cmp_node_by_idx);

    cout << "YES" << endl;
    for(int i = 0; i < N; i++)
        cout << T[i].p << " " << T[i].lc << " " << T[i].rc << endl;

    return 0;
}
