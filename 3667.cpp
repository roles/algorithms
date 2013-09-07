#include<cstdio>

#define maxn 100000
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

typedef struct roominfo{
    int left, cnt;
} roominfo;

roominfo room[maxn];

void build(int l, int r, int rt){
    int m;
    if(l == r){
        room[rt].left = l;
        room[rt].cnt = 1;
    }else{
        m = (l + r) >> 1; 
        build(lson);
        build(rson);
        room[rt].left = l;
        room[rt].cnt = room[rt << 1].cnt + room[rt << 1 | 1].cnt;
    }
}

roominfo query(int a, int b, int l, int r, int rt){
    roominfo ra, rb, ret;
    int m;

    if(a <= l && b >= r){
        return room[rt]; 
    }else{
        m = (l + r) >> 1;
        
        if(m >= a)
            ra = query(a, b, lson);
        if(m < b)
            rb = query(a, b, rson);
        if(ra.left + ra.cnt == rb.left){
            ret.left = ra.left;
            ret.cnt = ra.cnt + rb.cnt;
        }else{
            if(ra.cnt >= rb.cnt){
                return ra;
            }else{
                return rb;
            }
        }
    }
}

int main(){
    roominfo r;
    build(1, 10, 1);
    r = query(3, 7, 1, 10, 1); 
    printf("left:%d\tcnt:%d\n", r.left, r.cnt);
    return 0;
}
