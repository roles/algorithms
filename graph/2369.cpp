#include <iostream>
#include <cstdio>

using namespace std;

int vis[1001];
int n[1001];
int ring_num[501];

int gcd(int a, int b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

int main(){
    int N;
    
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        int pn;
        vis[i] = 0;
        scanf("%d", &pn);
        n[i] = pn-1;
    }

    int k = 0;
    for(int i = 0; i < N; i++){
        if(vis[i] == 0){
            int u = i;
            while(vis[u] == 0){
                vis[u] = 1;
                ring_num[k]++;
                u = n[u];
            }
            k++;
        }
    }

    int en = ring_num[0];
    for(int i = 1; i < k; i++){
        en = en * ring_num[i] / gcd(max(en, ring_num[i]), min(en, ring_num[i])); 
    }

    cout << en << endl;

    return 0;
}
