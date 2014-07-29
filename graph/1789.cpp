#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 2001;
const int maxm = 2001 * 2002;
const int inf = 10000;

int e[maxn][maxn];
int d[maxn];
bool vis[maxn];
char code[maxn][10];
int N;

int main(){
    while(true){
        scanf("%d", &N);
        if(N == 0)
            break;

        for(int i = 0; i < N; i++){
            scanf("%s", code[i]);
            d[i] = inf;
            vis[i] = false;
        }
        d[0] = 0;

        for(int i = 0; i < N-1; i++)
            for(int j = i+1; j < N; j++){
                int diff = 0;
                for(int k = 0; k < 7; k++){
                    if(code[i][k] != code[j][k])
                        diff++;
                }
                e[i][j] = diff;
                e[j][i] = diff;
            }

        int vis_num = N;
        int min_tree = 0;
        while(vis_num > 0){
            int k;
            int min_d = inf;
            for(int i = 0; i < N; i++){
                if(!vis[i] && d[i] < min_d){
                    min_d = d[i];
                    k = i;
                }
            }
            min_tree += min_d;

            for(int i = 0; i < N; i++){
                if(!vis[i] && d[i] > e[k][i]){
                    d[i] = e[k][i];
                }
            }

            vis[k] = true;
            vis_num--;
        }

        printf("The highest possible quality is 1/%d.\n", min_tree);
    }
    return 0;
}
