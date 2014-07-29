#include <cstdio>
#include <map>
#include <string>
#include <iostream>

using namespace std;

const int maxn = 1000;
const double eps = 1e-8;

struct edge {
    int b, e;
    double d;
} e[10000];

double d[maxn];

int N, E, s;

bool bellman_ford(){
    while(true){
        bool has_relax = false;
        for(int i = 0; i < E; i++){
            if(d[e[i].e] + eps < d[e[i].b] * e[i].d){
                d[e[i].e] = d[e[i].b] * e[i].d;
                has_relax = true;
            }
        }

        if(d[s] > 1.0 + eps){
            return true;
        }

        if(!has_relax){
            return false;
        }
    }
}

int main(){
    int ncase = 0;
    char u_name[100], v_name[100], name[100];
    while(true){
        ncase++;
        scanf("%d", &N); 
        if(N == 0)
            break;

        map<string, int> name2id;
        for(int i = 0; i < N; i++){
            scanf("%s", name);
            name2id[name] = i;
        }
        
        scanf("%d", &E);

        for(int i = 0; i < E; i++){
            double rate;
            
            scanf("%s %lf %s", u_name, &rate, v_name);

            e[i].b = name2id[u_name];
            e[i].e = name2id[v_name];
            e[i].d = rate;
        }

        bool has_ring = false;
        for(int k = 0; k < N; k++){
            for(int i = 0; i < N; i++){
                d[i] = 0;
            }
            s = k;
            d[k] = 1;

            if(bellman_ford()){
                has_ring = true;
                break;
            }
        }
        if(has_ring)
            printf("Case %d: Yes\n", ncase);
        else
            printf("Case %d: No\n", ncase);

    }
    return 0;
}
