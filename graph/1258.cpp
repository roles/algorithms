#include <cstdio>

using namespace std;

const int maxn = 101;
const int inf = 200000;

int N;

int e[maxn][maxn];
int d[maxn];
bool vis[maxn];

int main(){
    while(true){
        if(scanf("%d", &N) == EOF)
            break;
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
        int min_tree = 0;
        while(nvis--){
            
            int min_d = inf;
            int k;
            for(int i = 0; i < N; i++){
                if(!vis[i] && d[i] < min_d){
                    min_d = d[i];
                    k = i;
                }
            }
            min_tree += min_d;
            vis[k] = true;

            for(int i = 0; i < N; i++){
                if(!vis[i] && d[i] > e[k][i]){
                    d[i] = e[k][i];
                }
            }
        }

        printf("%d\n", min_tree);
    }
    return 0;
}
