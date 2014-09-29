#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <string>

using namespace std;

const int maxnode = 100*100+5;
const int sigma_size = 128;
int nrow, ncol;     //模板的行数和列数

/*
 * AC自动机，Trie树和KMP失配边的结合
 */
struct AC {
    int ch[maxnode][sigma_size]; 
    //int val[maxnode];
    //vector<vector<int> > val;   //为了处理重复模板，却超时。。
    int val[maxnode][105];  //使用两个数组记录模板的重复，加速计算
    int vn[maxnode];
    int f[maxnode];     //失配函数
    int last[maxnode];  //last[j]表示结点j失配时往回走遇到的下一个单词结点编号
    int sz;

    int cnt[1005][1005];    //统计以该位置为左上角匹配的行数

    int idx(char c){
        return c;
    }

    void init(){
        sz = 1; 
        memset(ch[0], 0, sizeof(ch[0])); 
        memset(cnt, 0, sizeof(cnt));
        vn[0] = 0;
    }
    
    AC(){ 
        init();
    }

    void insert(char *s, int v){
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            if(!ch[u][c]){  //新建结点
                memset(ch[sz], 0, sizeof(ch[sz]));
                vn[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u][vn[u]++] = v;
    }

    /* 构建AC状态机的失配函数f和last函数 */
    void getFail(){     
        queue<int> q;
        f[0] = 0;
        for(int i = 0; i < sigma_size; i++){
            if(ch[0][i]){
                f[ch[0][i]] = 0;    //第一个结点的失配为0
                q.push(ch[0][i]);
                last[ch[0][i]] = 0;
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
                    last[v] = vn[f[v]] ? f[v] : last[f[v]];
                }else{
                    ch[u][i] = ch[f[u]][i];     //直接添加失配状态的子结点，避免的find时的失配边跳转
                }
            }
        }
    }

    /* 匹配成功时打印或记录 */
    void print(int u, int row, int col){
        if(u){
            for(int i = 0; i < vn[u]; i++){
                if(row >= val[u][i]){
                    cnt[row-val[u][i]][col]++;
                }
            }
            print(last[u], row, col);
        }
    }

    /* 对文本T进行模板匹配 */
    void find(char *T, int row){
        int u = 0, n = strlen(T);
        
        int v = 0;  //起始状态为0
        for(int i = 0; i < n; i++){
            int c = idx(T[i]);

            v = ch[v][c];   //跳转到下一个状态
            if(vn[v])      //匹配到一个单词结点
                print(v, row, i-ncol+1);
            else if(last[v])    //该结点能够失配跳到一个单词结点，例如shex和he，匹配到she时其实已经成功匹配了he
                print(last[v], row, i-ncol+1);
        }
    }
};

AC ac;
char T[1005][1005];

int main(){
    //freopen("in.txt", "r", stdin);
    int t;
    scanf("%d", &t);

    char line[1005];
    while(t--){
        ac.init();

        int m, n;
        scanf("%d%d", &m, &n);
        for(int i = 1; i <= m; i++){
            scanf("%s", T[i]);
        }

        scanf("%d%d", &nrow, &ncol);
        for(int i = 1; i <= nrow; i++){
            scanf("%s", line);
            ac.insert(line, i);
        }

        ac.getFail();

        for(int i = 1; i <= m; i++){
            ac.find(T[i], i);
        }

        int ans = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(ac.cnt[i][j] == nrow){
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
