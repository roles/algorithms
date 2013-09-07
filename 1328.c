#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef struct interval{
    double l, r;
} interval;

int p[10000][2];
interval inter[10000];
int m[10000];

int cmp_inter(const void *a, const void *b){
    double ar = ((interval*)(a))->r, br = ((interval*)(b))->r;
    if(ar < br){
        return -1;
    }else if(ar > br){
        return 1;
    }else{
        return ((interval*)(b))->l - ((interval*)(a))->l;
    }
}

int main(){

    int i;
    int d, n;
    int r, cases;
    int is_err;
    double lim;

    freopen("input.txt", "r", stdin);
    memset(m, 0, sizeof(m));
    cases = 0;

    while(scanf("%d%d", &n, &d)){
        cases++;
        if(n == 0)
            break;
       
        is_err = 0;
        for(i = 0; i < n; i++){
            scanf("%d%d", &p[i][0], &p[i][1]);
            if(d >= p[i][1]){
                inter[i].l = p[i][0] - sqrt(1.0 * (d * d - p[i][1] * p[i][1])); 
                inter[i].r = p[i][0] + sqrt(1.0 * (d * d - p[i][1] * p[i][1]));
            }else{
                is_err = 1;
                continue;
            }

            //printf("%.2lf %.2lf\n", inter[i].l, inter[i].r);
        }
        if(is_err){
            printf("Case %d: %d\n", cases, -1);
            continue;
        }
        qsort(inter, n, sizeof(interval), cmp_inter);

        r = 1;
        lim = inter[0].r;

        for(i = 1; i < n; i++){
            if(lim >= inter[i].l)
                continue;
            lim = inter[i].r;
            r++;
        }
        printf("Case %d: %d\n", cases, r);
    }

    return 0;
}
