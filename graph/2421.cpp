#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

struct edge {
    int b, e;
    int len;

    bool operator<(const edge& x) const{
        if(len < x.len)
            return true;
        return false;
    }
};

int par[101];
edge E[10001];

void make_set(int a){
    par[a] = a;
}

int find_set(int a){
    if(a != par[a]){
        par[a] = find_set(par[a]);
    }
    return par[a];
}

void union_set(int a, int b){
    int pa = find_set(a);
    int pb = find_set(b);
    if(pa != pb){
        par[pb] = pa; 
    }
}


int main(){
    int N;
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        make_set(i);
    }

    int k = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int d;
            scanf("%d", &d);

            if((i < j) && (d > 0)){
                E[k].b = i;
                E[k].e = j;
                E[k].len = d;
                k++;
            }
        }
    }

    sort(E, E+k);

    int Q;
    scanf("%d", &Q);
    for(int i = 0; i < Q; i++){
        int b, e;
        scanf("%d%d", &b, &e);
        b--;
        e--;
        
        union_set(b, e);
    }

    int road_len = 0;
    for(int i = 0; i < k; i++){
        if(find_set(E[i].b) != find_set(E[i].e)){
            road_len += E[i].len; 
            union_set(E[i].b, E[i].e);
        }
    }

    cout << road_len << endl;
    
    return 0;
}

