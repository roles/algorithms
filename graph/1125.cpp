#include <cstdio>

const int maxn = 101;
const int inf = 1001;

using namespace std;

int N;
int d[maxn][maxn];
//int pi[maxn][maxn];

int main(){
    while(true){
        scanf("%d", &N);
        if(N == 0)
            break;

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i == j)
                    d[i][j] = 0;
                else
                    d[i][j] = inf;
                //pi[i][j] = -1;
            }
        }

        for(int i = 0; i < N; i++){
            int k;
            scanf("%d", &k);
            for(int j = 0; j < k; j++){
                int v, len;
                scanf("%d%d", &v, &len);

                d[i][v-1] = len;
                //pi[i][v-1] = i;
            }
        }

        for(int k = 0; k < N; k++){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    if(d[i][j] > d[i][k] + d[k][j]){
                        d[i][j] = d[i][k] + d[k][j];
                        //记录j的前驱
                        //pi[i][j] = pi[k][j];
                    }
                }
            }
        }

        int k;
        int min_d = inf;
        for(int i = 0; i < N; i++){
            int max_d = -1;
            for(int j = 0; j < N; j++){
                if(d[i][j] > max_d)
                    max_d = d[i][j];
            }
            if(max_d < min_d){
                min_d = max_d;
                k = i;
            }
        }

        if(min_d == inf)
            printf("disjoint\n");
        else
            printf("%d %d\n", k+1, min_d);
    }

    return 0;
}
