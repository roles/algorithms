/*
 * Trie树是空间换时间，减少无谓的字符串比较，Trie树对key有要求，一般英文字母key比较少好用
 * 并查集判断是否连通
 * 欧拉回路的判断：最多存在两个度数为偶数的点
 */

#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 5000000;

int p[maxn], deg[maxn];

void make_set(int i){
    p[i] = i;
}

int find_set(int i){
    if(p[i] != i)
        p[i] = find_set(p[i]);
    return p[i];
}

int union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a != b){
        p[b] = a;
    }
}

struct trie_node {
    int id;
    int next[26];
    trie_node() {
        id = -1;
    }
} T[maxn];

int node_num;
int stick_num;

int trie_find_insert(char *color){
    int len = strlen(color);
    int idx = 0;
    for(int i = 0; i < len; i++){
        int c = color[i] - 'a';
        if(!T[idx].next[c]){
            T[idx].next[c] = ++node_num;
        } 
        idx = T[idx].next[c]; 
    }
    if(T[idx].id == -1){
        T[idx].id = stick_num++;
    }
    return T[idx].id;
}

int main(){
    node_num = 0; 
    stick_num = 0;
    for(int i = 0; i < maxn; i++)
        p[i] = i;
    int odd = 0, suc = 1;

    while(true){
        char a[11], b[11];
        if(scanf("%s %s", a, b) == EOF)
            break;
        int aid = trie_find_insert(a);
        int bid = trie_find_insert(b);

        deg[aid]++;
        deg[bid]++;

        union_set(aid, bid);
    }

    int pid = find_set(0);
    for(int i = 0; i < stick_num && suc; i++){
        if(pid != find_set(i))
            suc = 0;
        if(deg[i] % 2)
            odd++;
        if(odd > 2)
            suc = 0;
    }
    if(suc)
        printf("Possible\n");
    else
        printf("Impossible\n");
    return 0;
}
