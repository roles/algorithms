#include <cstring>
#include <cstdio>

using namespace std;

const int maxnode = 4005 * 105;
const int maxlen = 300005;
const int sigma_size = 26;

char str[maxlen];
int d[maxlen];

struct Trie {
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz;

    void init(){
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }

    Trie() {
        init();
    }
    
    int idx(char c){
        return c - 'a';
    }

    void insert(char *s, int v){
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
        val[u] = v;
    }

    int query(char *s, int d[], int k){
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            if(!ch[u][c]){
                return 0;
            }
            u = ch[u][c];
            if(val[u]){     //若为单词结点
                d[k] = (d[k] + d[k+i+1]) % 20071027;
            }
        }
        return val[u];
    }
};

Trie T;

int main(){
    int ncase = 0;
    while(scanf("%s", str) == 1){
        T.init();
        int m;
        scanf("%d", &m);

        char word[105];
        while(m--){
            scanf("%s", word);
            T.insert(word, 1);
        }
        memset(d, 0, sizeof(d));

        int len = strlen(str);
        
        //d[i] = sum{d[i+len(x)] |单词x是S[i..L]的前缀 |}
        //从最后一个字符往前递推
        d[len] = 1;
        for(int i = len-1; i >= 0; i--){
            T.query(str+i, d, i);
        }

        printf("Case %d: %d\n", ++ncase, d[0]);
    }
    return 0;
}
