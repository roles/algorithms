#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <string>

using namespace std;

const int maxnode = 155 * 70;
const int sigma_size = 26;

/*
 * AC自动机，Trie树和KMP失配边的结合
 */
struct AC {
    int ch[maxnode][sigma_size]; 
    int val[maxnode];
    int f[maxnode];     //失配函数
    int last[maxnode];  //last[j]表示结点j失配时往回走遇到的下一个单词结点编号
    int sz;

    int cnt[155];   //每个单词成功匹配的次数
    map<string, int> m; //每个字符串与其val的对应关系

    int idx(char c){
        return c - 'a';
    }

    void init(){
        sz = 1; 
        memset(ch[0], 0, sizeof(ch[0])); 
        memset(cnt, 0, sizeof(cnt));
    }
    
    AC() { 
        init();
    }

    void insert(char *s, int v){
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            if(!ch[u][c]){  //新建结点
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
        m[string(s)] = v;
    }

    /* 构建AC状态机的失配函数f和last函数 */
    void getFail(){     
        queue<int> q;
        f[0] = 0;
        for(int i = 0; i < sigma_size; i++){
            if(ch[0][i]){
                f[ch[0][i]] = 0;    //第一个结点的失配为0
                q.push(ch[0][i]);
            }
        }

        while(!q.empty()){
            int u = q.front(); q.pop(); //u相当于KMP中的状态i
            for(int i = 0; i < sigma_size; i++){
                int v = ch[u][i];       //v相当于KMP中的状态i+1
                if(v){
                    q.push(v);
                    int r = f[u];
                    while(r && !ch[r][i])   //ch[r][i]!=0相当于KMP中P[r]==P[i]
                        r = f[r];
                    f[v] = ch[r][i];        //ch[r][i]不为0时，相当于KMP中f[i+1]=r+1;

                    //若失配跳转结点f[v]为单词结点则记为last[v]
                    //否则跳到last[f[v]]
                    last[v] = val[f[v]] ? f[v] : last[f[v]];
                }
            }
        }
    }

    /* 匹配成功时打印或记录 */
    void print(int u){
        if(u){
            cnt[val[u]]++;  //该单词结点匹配次数增加
            print(last[u]);
        }
    }

    /* 对文本T进行模板匹配 */
    void find(char *T){
        int u = 0, n = strlen(T);
        
        int v = 0;  //起始状态为0
        for(int i = 0; i < n; i++){
            int c = idx(T[i]);
            while(v && !ch[v][c])
                v = f[v];
            v = ch[v][c];   //跳转到下一个状态
            if(val[v])      //匹配到一个单词结点
                print(v);
            else if(last[v])    //该结点能够失配跳到一个单词结点，例如shex和he，匹配到she时其实已经成功匹配了he
                print(last[v]);
        }
    }
};

AC ac;
char T[1000005];
char P[155][75];

int main(){
    int m;
    while(true){
        scanf("%d", &m);
        if(!m) break;

        ac.init();
        for(int i = 1; i <= m; i++){
            scanf("%s", P[i]);
            ac.insert(P[i], i);     //val值不为0，故从1开始
        }
        scanf("%s", T);

        ac.getFail();
        ac.find(T);

        int best = -1;
        for(int i = 1; i <= m; i++){
            int c = ac.cnt[i];
            if(c > best)
                best = c;
        }
        printf("%d\n", best);
        for(int i = 1; i <= m; i++){
            if(ac.cnt[ac.m[string(P[i])]] == best)
                printf("%s\n", P[i]);
        }
    }
    return 0;
}
