#include <cstdio>
#include <cstring>

using namespace std;

const int maxnode = 4005*1005;
const int sigma_size = 64;


/*
 * 左孩子右兄弟的表示方式更节省空间，但是如果同一字符有多个后缀
 * 则检索效率会下降
 */
struct Trie {
    int ch[maxnode];    //左孩子
    int next[maxnode];  //右兄弟
    int key[maxnode];   //节点对应的字符
    int sz;
    int count[maxnode]; //该结点及其子结点包含的单词节点数

    void init(){
        sz = 1;
        ch[0] = 0;
        next[0] = 0;
        count[0] = 0;
    }

    Trie(){
        init(); 
    }

    void insert(char *s){
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++){
            bool found = false;
            int v;
            for(v = ch[u]; v != 0; v = next[v])
                if(key[v] == s[i]){
                    found = true;
                    break;
                }
            if(!found){     //新建节点
                ch[sz] = 0;
                key[sz] = s[i];
                count[sz] = 0;
                next[sz] = ch[u];   //头部插入

                ch[u] = sz;
                v = sz++;
            }
            count[u]++;
            u = v;
        }
        count[u]++;
    }

    long long getCmp(int u, int depth){
        long long res = 0;
        int cnt = count[u];
        for(int v = ch[u]; v != 0; v = next[v])     //统计该结点的单词数
            cnt -= count[v];
        if(cnt > 1){    //若该结点的单词多于一个，则两个相同的单词会产生2*(depth+1)次比较，共有cnt*(cnt-1)/2对
            res += cnt * (cnt-1) * (depth+1);
        }
        if(ch[u] != 0){
            int sum = 0;
            sum += cnt * (count[u] - cnt);  
            for(int v = ch[u]; v != 0; v = next[v])     //统计在该产生不同的字符串对数
                sum += (count[u] - count[v]) * count[v];
            res += sum / 2 * (2 * depth + 1);   //每一对不同字符串产生2*depth+1次比较

            for(int v = ch[u]; v != 0; v = next[v])     //继续统计该字符相同的字符串产生的比较
                res += getCmp(v, depth+1);
        }
        return res;
    }
};

Trie T;

int main(){
    int ncase = 0;
    char word[1005];
    while(true){
        T.init();
        int m;
        scanf("%d", &m);
        if(m == 0)
            break;
        while(m--){
            scanf("%s", word);
            T.insert(word);
        }
        printf("Case %d: %lld\n", ++ncase, T.getCmp(0, 0));
    }
    return 0;
}
