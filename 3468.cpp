#include<cstdio>
#include<cstring>

#define maxn 100005
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

long long sum[maxn << 2], val[maxn];
int mark[maxn << 2];

void pushup(int rt){
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void pushdown(int rt, int c){
    if(mark[rt]){
        mark[rt << 1] += mark[rt];
        mark[rt << 1 | 1] += mark[rt];
        sum[rt << 1] += mark[rt] * (c - (c >> 1));
        sum[rt << 1 | 1] += mark[rt] * (c >> 1);
        mark[rt] = 0;
    }
}

void build(int l, int r, int rt){
    int m;

    if(l == r){
        sum[rt] = val[l];
        return;
    }
    m = (l + r) >> 1;
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int L, int R, int l, int r, int rt, int c){
    int m;

    if(l >= L && r <= R){
        mark[rt] = c;
        sum[rt] += (r - l + 1) * c;
        return;
    }
    pushdown(rt, r - l + 1);

    m = (l + r) >> 1;
    if(m >= L)
        update(L, R, lson, c);
    if(m < R)
        update(L, R, rson, c);
    //修改操作要对祖先节点也做相应的修改
    pushup(rt);
}

long long query(int L, int R, int l, int r, int rt){
    int m;
    long long ret;

    if(l >= L && r <= R){
        return sum[rt]; 
    }
    //在需要查询孩子的时候才执行延迟标识操作
    pushdown(rt, r - l + 1);
    m = (l + r) >> 1;
    ret = 0;
    if(m >= L)
        ret += query(L, R, lson); 
    if(m < R)
        ret += query(L, R, rson);
    return ret;
}

int main(){
    
    int N, Q;
    int i;
    char op[1];
    int from, to, c;

    freopen("input.txt", "r", stdin); 

    memset(mark, 0, sizeof(mark));
    scanf("%d%d", &N, &Q);
    for(i = 1; i <= N; i++){
        scanf("%lld", &val[i]); 
    }
    build(1, N, 1);

    for(i = 0; i < Q; i++){
        scanf("%s", op);
        if(op[0] == 'C'){
            scanf("%d%d%d", &from, &to, &c); 
            update(from, to, 1, N, 1, c);
        }else{
            scanf("%d%d", &from, &to);
            printf("%lld\n", query(from, to, 1, N, 1));
        }
    }

    return 0;
}
