#include<stdio.h>
#include<stdlib.h>

#define MAXN 250001
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

struct point {
    int x, y;
    int i;
} p[MAXN];

int N;
int begin, end, tl;

int cmp_point_x(const void *a, const void *b){
    int ret;
    ret = ((struct point*)a)->x - ((struct point*)b)->x;
    if(ret != 0){
        return ret; 
    }else{
        return ((struct point*)a)->y - ((struct point*)b)->y;
    }
}

int cmp_point_y(const void *a, const void *b){
    int ret;
    ret = ((struct point*)a)->y - ((struct point*)b)->y;
    if(ret != 0){
        return ret; 
    }else{
        return ((struct point*)a)->x - ((struct point*)b)->x;
    }
}

void solve(){
    int i, j;
    int l;
    int b, e;

    qsort(p, N, sizeof(struct point), cmp_point_x);
    for(i = 0; i < N-1; i++){
        if(p[i].x == p[i+1].x && abs(p[i].i - p[i+1].i) != 1){  
            l = p[i+1].y - p[i].y;   
            b = min(p[i].i, p[i+1].i);
            e = max(p[i].i, p[i+1].i);
            if(l < tl || (l == tl && b < begin) || (l == tl && b == begin && e > end)){
                tl = l;
                begin = b;
                end = e;
            }
        }
    }
    qsort(p, N, sizeof(struct point), cmp_point_y);
    for(i = 0; i < N-1; i++){
        if(p[i].y == p[i+1].y && abs(p[i].i - p[i+1].i) != 1){  
            l = p[i+1].x - p[i].x;   
            b = min(p[i].i, p[i+1].i);
            e = max(p[i].i, p[i+1].i);
            if(l < tl || (l == tl && b < begin) || (l == tl && b == begin && e > end)){
                tl = l;
                begin = b;
                end = e;
            }
        }
    }
}

int main(){
    int i, j;
    int x, y;
    char s;

    freopen("input.txt", "r", stdin);
    scanf("%d", &N);
    getchar();
    N++;

    x = y = 0;
    p[0].x = p[0].y = 0;
    p[0].i = 0;
    tl = MAXN;
    for(i = 1; i < N; i++){
        scanf("%c", &s);
        switch(s){
            case 'N':
                y++;
                break;
            case 'S':
                y--;
                break;
            case 'E':
                x++;
                break;
            case 'W':
                x--;
                break;
        }
        p[i].x = x;
        p[i].y = y;
        p[i].i = i;
    }
    solve();
    printf("%d\t%d\n", begin, end);
    for(i = 0; i < N; i++){
        printf("%d:\t(%d,%d)\n", p[i].i, p[i].x, p[i].y);
    }
    return 0;
}
