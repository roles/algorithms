#include <cstdio>

using namespace std;

const int maxn = 501;
const int inf = 100000;

int N;

int e[maxn][maxn];
int d[maxn];
bool vis[maxn];

int main(){
    int ncase;
    scanf("%d", &ncase);
    while(ncase--){
        scanf("%d", &N);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                int len;
                scanf("%d", &len);
                e[i][j] = len;
            }
        }

        for(int i = 0; i < N; i++){
            vis[i] = false;
            d[i] = inf;
        }
        d[0] = 0;

        int nvis = N;
        int max_d = 0;
        while(nvis--){
            
            int min_d = inf;
            int k;
            for(int i = 0; i < N; i++){
                if(!vis[i] && d[i] < min_d){
                    min_d = d[i];
                    k = i;
                }
            }
            if(min_d > max_d)
                max_d = min_d;
            vis[k] = true;

            for(int i = 0; i < N; i++){
                if(!vis[i] && d[i] > e[k][i]){
                    d[i] = e[k][i];
                }
            }
        }

        printf("%d\n", max_d);
    }
    return 0;
}
