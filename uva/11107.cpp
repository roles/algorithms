#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

/*
 * 多个字符串中重复出现的子串
 * 用数字代替字符来进行计算，末端插入的字符就可以用数字表示了
 */

const int maxlen = 101000;

int v[maxlen];
int b[maxlen], ans[maxlen];   //数组b表示合成串中的位置属于哪一个原始串,数组ans记录匹配的位置
int sa[maxlen], t[maxlen], t2[maxlen], c[maxlen];
int rankv[maxlen], height[maxlen];
int flag[110];

int build_sa(int n, int m){
    int i, *x = t, *y = t2;

    //先构造第一轮的sa和x，K=1
    for(i = 0; i < m; i++)  c[i] = 0;
    for(i = 0; i < n; i++)  c[x[i] = v[i]]++;   //第一轮的x[i]并不是从0开始编号
    for(i = 1; i < m; i++)  c[i] += c[i-1];
    for(i = n-1; i >= 0; i--){
        sa[--c[x[i]]] = i;
    }

    for(int k = 1; k <= n; k <<= 1){
        int p = 0;

        for(i = n-k; i < n; i++)
            y[p++] = i; 
        for(i = 0; i < n; i++){
            if(sa[i] >= k)  
                y[p++] = sa[i]-k;
        }

        for(i = 0; i < m; i++)  c[i] = 0;
        for(i = 0; i < n; i++)  c[x[y[i]]]++;
        for(i = 1; i < m; i++)  c[i] += c[i-1];
        for(i = n-1; i >= 0; i--){
            sa[--c[x[y[i]]]] = y[i];
        }

        swap(x, y);
        p = 1;  
        x[sa[0]] = 0;

        for(i = 1; i < n; i++){     
            x[sa[i]] = y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k] ?  
                p-1 : p++;
        }

        if(p >= n) break;
        m = p;
    }

}

/* 
 * 若字符串T是字符串S的字串，则T必定是S某个后缀的前缀
 * 查找模板P在文本串s中的位置，n为文本串长度 
 */
void getHeight(int n){
    int i, j, k = 0;
    for(i = 0; i < n; i++)  rankv[sa[i]] = i;
    for(i = 0; i < n; i++){
        if(k) k--;
        if(rankv[i] == 0){
            height[rankv[i]] = k = 0;
            continue;
        }
        j = sa[rankv[i]-1];     //j表示下标i在后缀数组中的前一个后缀的下标
        while(v[i+k] == v[j+k]) k++;
        height[rankv[i]] = k;
    }
}

int char2idx(char c){
    return c - 'a';
}

char idx2char(int x){
    return 'a' + x;
}

char str[1010];

int main(){
    int n;
    bool firstCase = true;

    //freopen("in.txt", "r", stdin);

    while(true){
        int nchar = 0;  //拼接之后的字符串总长度
        int mlen = 0;

        scanf("%d", &n);
        if(n == 0) break;
        for(int i = 0; i < n; i++){
            scanf("%s", str);
            int len = strlen(str);
            if(len > mlen)  mlen = len;

            for(int j = 0; j < len; j++){
                v[nchar++] = char2idx(str[j]);
                b[nchar-1] = i;
            }
            //每个字符串的末端插入一个不重复的特殊字符
            //如果不插入末端字符，则有的字符串可能在后缀树中不是一个叶子结点
            v[nchar++] = 26 + i;
            b[nchar-1] = i;
        }

        if(n == 1){     //一个字符串的时候判断是否属于同一分组会有问题，因此做特殊处理
            if(!firstCase)
                printf("\n%s\n", str);
            else{
                firstCase = false;
                printf("%s\n", str);
            }
            continue;
        }

        build_sa(nchar, 26+n);
        getHeight(nchar);

        int l = 1, r = mlen;
        bool valid = false;
        int numAns = 0;
        while(l <= r){
            int m = l + (r-l)/2;
            memset(flag, 0, sizeof(flag));            
            valid = false;

            for(int i = 1; i < nchar; i++){
                if(height[i] < m){
                    int mat = 0;
                    for(int j = 0; j < n; j++){
                        mat += flag[j];
                    }
                    if(mat > n/2){
                        if(!valid)  numAns = 0;     //当存在解时才覆盖上一个解
                        valid = true;
                        ans[numAns++] = sa[i-1];
                    }
                    memset(flag, 0, sizeof(flag));
                }else{
                    flag[b[sa[i-1]]] = 1;
                    flag[b[sa[i]]] = 1;
                }
            }
            if(valid){
                l = m + 1;
            }else{
                r = m - 1;
            }
        }
        if(!firstCase)
            printf("\n");
        else
            firstCase = false;
        if(r < 1){
            printf("?\n");
        }else{
            for(int i = 0; i < numAns; i++){
                for(int j = ans[i]; j < ans[i]+r; j++){
                    printf("%c", idx2char(v[j]));
                }
                printf("\n");
            }
        }
    }
    return 0;
}
