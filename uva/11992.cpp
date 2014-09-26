#include <cstdio>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

struct Result {
    int sum, max, min;

    Result():sum(0), min(INT_MAX), max(-1){}
};

const int maxr = 25;
const int maxc = 100010<<2;

int minv[maxr][maxc];
int maxv[maxr][maxc];
int sumv[maxr][maxc];
int addv[maxr][maxc];
int setv[maxr][maxc];

/*
 * pushdown 
 * 传递set标记时要将子结点的add标记清除
 * 传递add标记则累加子结点的add标记
 */
void pushdown(int idx, int o){
    int lc = o*2, rc = o*2+1;    
    if(setv[idx][o] >= 0){
        setv[idx][lc] = setv[idx][rc] = setv[idx][o];
        addv[idx][lc] = addv[idx][rc] = 0; //清除子结点add标记
        setv[idx][o] = -1;
    }
    if(addv[idx][o] > 0){
        addv[idx][lc] += addv[idx][o];
        addv[idx][rc] += addv[idx][o];
        addv[idx][o] = 0;
    }
}

/*
 * 
 */
void maintain(int idx, int o, int L, int R){
    int lc = o*2, rc = o*2+1;    
    if(L < R){
        sumv[idx][o] = sumv[idx][lc] + sumv[idx][rc];
        maxv[idx][o] = max(maxv[idx][lc] , maxv[idx][rc]);
        minv[idx][o] = min(minv[idx][lc] , minv[idx][rc]);
    }else{      //叶子结点还原
        sumv[idx][o] = 0;
        maxv[idx][o] = 0;
        minv[idx][o] = 0;
    }
    if(setv[idx][o] != -1){
        sumv[idx][o] = setv[idx][o] * (R-L+1);
        maxv[idx][o] = setv[idx][o];
        minv[idx][o] = setv[idx][o];
    }
    if(addv[idx][o] != 0){
        sumv[idx][o] += addv[idx][o] * (R-L+1);
        maxv[idx][o] += addv[idx][o];
        minv[idx][o] += addv[idx][o];
    }
}

void add(int idx, int y1, int y2, int v, int o, int L, int R){
    int lc = o*2, rc = o*2+1;
    if(y1 <= L && y2 >= R){
        addv[idx][o] += v;
    }else{
        pushdown(idx, o);
        int M = L + (R-L) / 2;
        if(y1 <= M)
            add(idx, y1, y2, v, o*2, L, M);
        else
            maintain(idx, o*2, L, M);

        if(y2 > M)
            add(idx, y1, y2, v, o*2+1, M+1, R);
        else
            maintain(idx, o*2+1, M+1, R);
    }
    maintain(idx, o, L, R);
}

void set(int idx, int y1, int y2, int v, int o, int L, int R){
    int lc = o*2, rc = o*2+1;
    if(y1 <= L && y2 >= R){
        setv[idx][o] = v;
        addv[idx][o] = 0;
    }else{
        pushdown(idx, o);
        int M = L + (R-L) / 2;
        if(y1 <= M)
            set(idx, y1, y2, v, o*2, L, M);
        else
            maintain(idx, o*2, L, M);

        if(y2 > M)
            set(idx, y1, y2, v, o*2+1, M+1, R);
        else
            maintain(idx, o*2+1, M+1, R);
    }
    maintain(idx, o, L, R);
}

void query(int idx, int y1, int y2, int o, int L, int R, int add, Result &res){
    if(setv[idx][o] >= 0){
        res.sum += (setv[idx][o] + add + addv[idx][o]) * (min(R,y2) - max(L,y1) + 1);
        res.max = max(res.max, setv[idx][o] + add + addv[idx][o]);
        res.min = min(res.min, setv[idx][o] + add + addv[idx][o]);
    }else if(y1 <= L && y2 >= R){ //边界区间
        res.sum += sumv[idx][o] + add * (R-L+1);
        res.max = max(res.max, maxv[idx][o] + add);
        res.min = min(res.min, minv[idx][o] + add);
    }else{
        int M = L + (R-L)/2;
        if(y1 <= M)
            query(idx, y1, y2, o*2, L, M, add+addv[idx][o], res);
        if(y2 > M)
            query(idx, y1, y2, o*2+1, M+1, R, add+addv[idx][o], res);
    }
}

int main(){
    int r, c, m;

    while(scanf("%d%d%d", &r, &c, &m) == 3){
        bzero(minv, sizeof(minv));
        bzero(maxv, sizeof(maxv));
        bzero(sumv, sizeof(sumv));
        bzero(addv, sizeof(addv));
        for(int i = 0; i <= r; i++)
            for(int j = 0; j <= c*2; j++)
                setv[i][j] = -1;

        while(m--){
            int cmd;
            scanf("%d", &cmd);
            int x1, x2, y1, y2;
            int v;
            switch(cmd){
                case 1: 
                    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
                    for(int x = x1; x <= x2; x++){
                        add(x, y1, y2, v, 1, 1, c);
                    }
                    break;
                case 2:
                    scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
                    for(int x = x1; x <= x2; x++){
                        set(x, y1, y2, v, 1, 1, c);
                    }
                    break;
                case 3:
                    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                    Result res;
                    for(int x = x1; x <= x2; x++){
                        query(x, y1, y2, 1, 1, c, 0, res);
                    }
                    printf("%d %d %d\n", res.sum, res.min, res.max);
                    break;
            }
        }
    }

    return 0;
}
