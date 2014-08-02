#include <cstdio>
#include <cstring>

const int maxn = 27;
const int maxm = 27*27;

struct edge {
    int b, e;
} e[maxm];

enum result {
    SORTED, NOT_DETERMINED, INCONSISTENCY   
};

int in[maxn];
int out[maxn];
int first_e[maxm], next_e[maxm];
int st[maxn];
int vis[maxn], show[maxn];

int N, E;

result toposort(int num_edge, int num_v){
    bool not_deter = false;
    memset(in, 0, sizeof(in));
    for(int j = 0; j < num_edge; j++){
        in[e[j].e]++;
    }

    int front = 0, rear = 0;
    for(int i = 0; i < N; i++){
        if(show[i] && in[i] == 0)
            st[rear++] = i;
    }
    //存在多个并列的点则依然没有全局有序
    if(rear-front > 1)
        not_deter = true;

    int nvis = 0;
    while(front != rear){
        int u = st[--rear]; 

        for(int i = first_e[u]; i != -1; i = next_e[i]){
            int v = e[i].e; 
            in[v]--;
            if(in[v] == 0){
                st[rear++] = v;
            }
        }
        if(rear-front > 1){
            not_deter = true;
        }
        out[nvis++] = u;
    }

    //仍有没有进栈的点说明有环
    if(nvis != num_v)
        return INCONSISTENCY;
    else if(num_v != N || not_deter)
        return NOT_DETERMINED;
    else
        return SORTED;

}

int main(){
    while(true){
        scanf("%d%d", &N, &E);
        if(N == 0 && E == 0)
            break;

        char c = getchar();
        while(c != '\n')
            c = getchar();

        for(int i = 0; i < N; i++){
            first_e[i] = -1;
            show[i] = 0;
        }

        int num_v = 0;
        bool is_stop = false;
        for(int i = 0; i < E; i++){
            char str[5];
            gets(str);
            if(is_stop)
                continue;
            e[i].b = str[0] - 'A';
            e[i].e = str[2] - 'A';
            next_e[i] = first_e[e[i].b];
            first_e[e[i].b] = i;

            if(show[e[i].b] == 0){
                show[e[i].b] = 1;
                num_v++;
            }
            if(show[e[i].e] == 0){
                show[e[i].e] = 1;
                num_v++;
            }

            switch(toposort(i+1, num_v)){
                case SORTED:
                    printf("Sorted sequence determined after %d relations: ", i+1);
                    for(int j = 0; j < N; j++){
                        printf("%c", 'A' + out[j]);
                    }
                    printf(".\n");
                    is_stop = true;
                    break;
                case NOT_DETERMINED:
                    break;
                case INCONSISTENCY:
                    printf("Inconsistency found after %d relations.\n", i+1);
                    is_stop = true;
                    break;
            }
        }

        if(!is_stop)
            printf("Sorted sequence cannot be determined.\n");
    }

    return 0;
}
