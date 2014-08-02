#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 151;
const int inf = 1000;

struct point {
    int x, y;
    int d;
} q[maxn*maxn], p[maxn];

int e[maxn][maxn];
int d[maxn];
int vis[maxn], mvis[maxn][maxn];
char m[maxn][maxn], midx[maxn][maxn];
int N;
int di[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
int x, y;

int main(){
    int ncase;
    scanf("%d", &ncase);
    while(ncase--){
        scanf("%d%d", &y, &x);
        N = 0;

        char c;
        c = getchar();
        while(c != '\n')
        {
            c = getchar();
        }
        for(int i = 0; i < x; i++){
            gets(m[i]);
        }

        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++){
                if(m[i][j] == 'S' || m[i][j] == 'A'){
                    p[N].x = i;
                    p[N].y = j;
                    p[N].d = 0;
                    
                    midx[i][j] = N;
                    N++;
                }
            }


        for(int k = 0; k < N; k++){

            memset(mvis, 0, sizeof(mvis));
            point cur = p[k];
            e[k][k] = 0;

            int front = 0, rear = 0;
            q[rear++] = cur;
            while(front != rear){
                point u = q[front++]; 
                mvis[u.x][u.y] = 1;

                for(int i = 0; i < 4; i++){
                    point v;
                    v.x = u.x + di[i][0];
                    v.y = u.y + di[i][1];
                    v.d = u.d + 1;
                    if(!mvis[v.x][v.y] && m[v.x][v.y] != '#'){
                        q[rear++] = v;
                        mvis[v.x][v.y] = 1;
                        if(m[v.x][v.y] == 'A' || m[v.x][v.y] == 'S'){
                            e[k][midx[v.x][v.y]] = v.d;
                        }
                    }
                }
            }
        }

        for(int i = 0; i < N; i++){
            d[i] = inf;            
            vis[i] = 0;
        }
        d[0] = 0;

        int min_tree = 0;
        for(int i = 0; i < N; i++){
            int k, min_d = inf;
            for(int j = 0; j < N; j++){
                if(!vis[j] && d[j] < min_d){
                    min_d = d[j];
                    k = j;
                }
            }
            vis[k] = 1;
            min_tree += min_d;

            for(int j = 0; j < N; j++){
                if(!vis[j] && d[j] > e[k][j]){
                    d[j] = e[k][j];
                }
            }
        }

        printf("%d\n", min_tree);
    }

    return 0;
}
