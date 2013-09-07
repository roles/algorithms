#include<cstdio>
#include<cstring>

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define maxn 200005

int pos[maxn], val[maxn], spa[maxn << 2];
int ans[maxn];

void pushup(int rt){
    spa[rt] = spa[rt << 1] + spa[rt << 1 | 1]; 
}

void build(int l, int r, int rt){
    int m;
    if(l == r){
        spa[rt] = 1;
        return;
    }
    m = (l + r) >> 1;
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int l, int r, int rt, int p, int v){
    int m;

    if(l == r){
        spa[rt] = 0;
        ans[l] = v;
        return;
    }
    m = (l + r) >> 1;
    if(p >= spa[rt << 1])
        update(rson, p - spa[rt << 1], v);
    else
        update(lson, p, v);
    pushup(rt);
}

int main(){

    int i, N;

    freopen("input.txt", "r", stdin);

    while(scanf("%d", &N) == 1){
        build(1, N, 1);
        memset(val, -1, sizeof(val));

        for(i = 0; i < N; i++){
            scanf("%d%d", &pos[i], &val[i]);
        }
        for(i = N - 1; i >= 0; i--){
            update(1, N, 1, pos[i], val[i]);
        }
        for(i = 1; i <= N; i++){
            if(i != N){
                printf("%d ", ans[i]);
            }else{
                printf("%d\n", ans[i]);
            }
        } 
    }


    return 0;   
}
