#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <string>

using namespace std;

const int maxnode = 405;
const int sigma_size = 62;

int N;
double prob[sigma_size];
int validChar[sigma_size];

int idx(char c){
    if(c >= '0' && c <= '9')
        return c - '0' + 52;
    if(c >= 'a' && c <= 'z')
        return c - 'a';
    return c - 'A' + 26;
}

/*
 * AC自动机，Trie树和KMP失配边的结合
 */
struct AC {
    int ch[maxnode][sigma_size]; 
    int val[maxnode];
    int f[maxnode];     //失配函数
    int last[maxnode];  //last[j]表示结点j失配时往回走遇到的下一个单词结点编号
    int sz;


    void init(){
        sz = 1; 
        memset(ch[0], 0, sizeof(ch[0])); 
        memset(vis, 0, sizeof(vis));
        memset(prob, 0, sizeof(prob));
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

                    //对AC自动机的改造，
                    val[v] |= val[f[v]];    

                    //若失配跳转结点f[v]为单词结点则记为last[v]
                    //否则跳到last[f[v]]
                    //last[v] = val[f[v]] ? f[v] : last[f[v]];
                }else{

                    //对AC自动机的改造，将失配状态的子结点变为自己的子结点
                    //这是一个递推的过程，层次最高的状态也会共享层次最低状态的子结点
                    ch[u][i] = ch[f[u]][i]; 
                }
            }
        }
    }

    /* 匹配成功时打印或记录 */
    void print(int u){
        if(u){
            printf("%d\n", u);
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

    double d[maxnode][105];
    int vis[maxnode][105];
    /*
     * 带备忘录的概率动态规划
     * 先要对AC自动机进行改造，使得状态能够指向其祖先失配状态的子结点，
     * 即在getFail中对不存在的ch[u][i]调用ch[u][i] = ch[f[u]][i]
     * 并且所有状态共享其祖先失配状态的单词结点判别，即val[u] |= val[f[u]]
     *
     * d[i,j]表示从结点i开始走j步，不碰到任何单词结点的概率
     * d[i,j]=sum{d(ch[i][k], j-1)} 
     * st k=1...N 且 val[ch[i][k]]==0为非单词节点
     */
    double getProb(int u, int L){
        if(L == 0)
            return 1.0;
        if(vis[u][L])
            return d[u][L];
        vis[u][L] = 1;
        double &ans = d[u][L];
        ans = 0.0;
        for(int i = 0; i < N; i++){
            int c = idx(validChar[i]);
            int v = u;
            if(!val[ch[v][c]]){     //只考虑非单词结点
                //由于对AC自动机的改造，即使状态v不存在子结点c
                //ch[v][c]仍可以直接跳到失配状态f[v]的子结点c
                ans += prob[c] * getProb(ch[v][c], L-1);
            }
        }
        return ans;
    }
};

AC ac;

int main(){
    //freopen("in.txt", "r", stdin);
    int ncase, Ncase;
    scanf("%d", &Ncase);
    char P[25];
    for(int ncase = 1; ncase <= Ncase; ncase++){
        int K, L;

        ac.init();
        scanf("%d", &K);
        
        while(K--){
            scanf("%s", P);
            ac.insert(P, 1);
        }
        scanf("%d", &N);
        for(int i = 0; i < N; i++){
            scanf("%s", P);
            validChar[i] = P[0];
            scanf("%lf", &prob[idx(validChar[i])]);
        }
        scanf("%d", &L);

        ac.getFail();

        printf("Case #%d: %.6lf\n", ncase, ac.getProb(0, L));
    }
        
    return 0;
}
