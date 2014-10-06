#include <cstring>
#include <cstdio>

using namespace std;

const int maxnode = 50000 * 200 + 100;
const int maxlen = 300005;
const int sigma_size = 2;

struct Trie {
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int cnt[maxnode];
    int sz;

    void init(){
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        cnt[0] = 0;
    }

    Trie() {
        init();
    }
    
    int idx(char c){
        return c - '0';
    }

    void insert(char *s, int v){
        int u = 0, n = strlen(s); 
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            if(!ch[u][c]){  //结点不存在
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                cnt[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
            cnt[u]++;
        }
        val[u] = v;
    }

    int dfs(int u, int h){
        int maxSet = 0;
        for(int i = 0; i < sigma_size; i++){
            if(ch[u][i]){
                int t = dfs(ch[u][i], h+1);
                if(t > maxSet)  maxSet = t;
            }
        }
        if(h*cnt[u] > maxSet)
            maxSet = h*cnt[u];
        return maxSet;
    }
};

Trie T;

int main(){
    int ncase = 0;
    scanf("%d", &ncase);

    char str[205];

    while(ncase--){
        T.init();

        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            scanf("%s", str);         
            T.insert(str, 1);
        }
        printf("%d\n", T.dfs(0, 0));
    }
    return 0;
}
