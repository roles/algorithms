#include <cstring>
#include <cstdio>

using namespace std;

const int maxnode = 10000 * 40 + 100;
const int sigma_size = 26;

struct Trie {
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int cnt;
    int prefixCount[sigma_size];
    int suffixCount[sigma_size];
    int sz;

    void init(){
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        cnt = 0;
        memset(prefixCount, 0, sizeof(prefixCount));
        memset(suffixCount, 0, sizeof(suffixCount));
    }

    Trie() {
        init();
    }
    
    int idx(char c){
        return c - 'a';
    }

    void insert_prefix(char *s, int v){
        int u = 0, n = strlen(s); 
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            if(!ch[u][c]){  //结点不存在
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
                cnt++;
                if(i >= 1) prefixCount[idx(s[i])]++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    void insert_suffix(char *s, int v){
        int u = 0, n = strlen(s); 
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            if(!ch[u][c]){  //结点不存在
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        if(val[u] == 0){
            cnt++;
            if(n > 1) suffixCount[idx(s[0])]++;
        }
        val[u] = v;
    }

};

Trie PT, ST;

int main(){
    char str[205];
    //freopen("in.txt", "r", stdin);

    while(true){
        PT.init();
        ST.init();

        int n, sum = 0;
        if(scanf("%d", &n) == EOF)
            break;
        for(int i = 0; i < n; i++){
            scanf("%s", str);         
            PT.insert_prefix(str, 1);
            int l = strlen(str);
            for(int j = 0; j < l; j++){
                ST.insert_suffix(str+j, 1);
            }
        }
        for(int i = 0; i < sigma_size; i++){
            sum += ST.suffixCount[i] * PT.prefixCount[i];
        }
        //printf("%d\t%d\t%d\t", ST.cnt, PT.cnt, sum);
        printf("%d\n", ST.cnt * PT.cnt - sum);
    }
    return 0;
}
