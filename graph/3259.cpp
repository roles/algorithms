#include <cstdio>

const int inf = 10005;

struct edge {
    int b, e;
    int l;
} E[5201];

int d[501];

int N, M, W, s;

bool bellman_ford(){
    while(true){
        bool relax = false;
        for(int i = 0; i < 2*M+W; i++){
            if(d[E[i].e] > d[E[i].b] + E[i].l){
                d[E[i].e] = d[E[i].b] + E[i].l;
                relax = true;
            }
        }

        if(d[s] < 0)
            return true;

        if(!relax)
            return false;
    }

}

int main(){
    int F;

    scanf("%d", &F);

    while(F--){
        scanf("%d%d%d", &N, &M, &W);

        for(int i = 0; i < M; i++){
            int a, b, l;
            scanf("%d%d%d", &a, &b, &l);

            E[2*i].b = a-1;  
            E[2*i].e = b-1;
            E[2*i].l = l;
            E[2*i+1].b = b-1;  
            E[2*i+1].e = a-1;
            E[2*i+1].l = l;
        }
        for(int i = 2*M; i < 2*M+W; i++){
            int a, b, l;
            scanf("%d%d%d", &a, &b, &l);

            E[i].b = a-1;  
            E[i].e = b-1;
            E[i].l = -l;
        }

        bool back = false;
        for(int i = 0; i < N; i++){

            for(int j = 0; j < N; j++)
                d[j] = inf;

            s = i;
            d[s] = 0;

            if(bellman_ford()){
                back = true;
                break;
            }
        }
        if(back)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
