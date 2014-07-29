#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn = 201;
const double inf = 10e8;

using namespace std;

struct point {
    int x, y;
    double d;
} stone[maxn];

double d[maxn][maxn];

bool vis[maxn];

int N;

void dijkstra(){
    
    for(int i = 0; i < N; i++){
        stone[i].d = inf;
        vis[i] = false;
    }
    stone[0].d = 0;

    int no_vis = N;

    while(no_vis > 0){
        double min_d = inf;
        int k;

        //不用优先队列，遍历一次找到最小的d及其index
        for(int i = 0; i < N; i++){
            if(!vis[i] && stone[i].d < min_d){
                min_d = stone[i].d;
                k = i;
            }
        }
        vis[k] = true;
        no_vis--;

        for(int i = 0; i < N; i++){
            if(!vis[i] && stone[i].d > max(stone[k].d, d[k][i])){
                stone[i].d = max(stone[k].d, d[k][i]);
            }
        }
    }
}

int main(){
    int ncase = 0;
    while(true){
        scanf("%d", &N);
        if(N == 0)
            break;
        ncase++;

        for(int i = 0; i < N; i++){
            scanf("%d%d", &stone[i].x, &stone[i].y);
        }

        for(int i = 0; i < N-1; i++){
            for(int j = i+1; j < N; j++){
                double len = sqrt((stone[i].x - stone[j].x) * (stone[i].x - stone[j].x) + 
                    (stone[i].y - stone[j].y) * (stone[i].y - stone[j].y));
                d[i][j] = d[j][i] = len;
            }
        }

        dijkstra();

        printf("Scenario #%d\n", ncase);
        printf("Frog Distance = %.3f\n\n", stone[1].d);
    }
     
    return 0;
}
