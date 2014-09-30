#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

/*
 * 对于一个长的文本串，后缀i表示以下标i开头的字符串后缀
 * 在计算后缀数组时，状态K表示当前状态的后缀的长度
 * (1) 后缀数组sa[i]表示在当前状态下，对后缀j按字典序从小到大的排序 [a, b, c...] 表示按字典序 后缀a < 后缀b < 后缀c...
 * (2) x[i]表示当前状态下每个位置的名次，编号从0开始，用作第一关键字
 * (3) 第二关键字是每个位置的后面第K个位置的名次，K为当前状态的后缀长度
 *     因此，最后K个位置都没有第二关键字，排名最高
 *     y[i]是当前状态下，根据第二关键字对位置的排序，后K个位置第二关键字不存在，优先度最高
 * (4) 数组rank[i]代表后缀i在sa数组中的下标
 * (5) 数组height[i]定义为sa[i]和sa[i-1]的最长公共前缀长度LCP，即排名相邻的两个后缀的最长公共前缀，两个字符串的LCP长度为k，
 *     意味着这两个字符串的前k个字符都相同，但第k+1个不同（或者某个字符串一共只有k个字符）
 *     假设rank[j]<rank[k]，不难证明后缀j和后缀k的LCP长度等于height[rank[j]+1], ...height[rank[k]中的最小值，即RMQ(height, rank[j]+1, rank[k])
 * (6) 辅助数组h[i]=height[rank[i]]表示下标为i的对应height值，按照h[1],h[2]...的顺序递推计算，因为h[i]>=h[i-1]-1，所以递推时能减少重复比较
 *
 * 在解决问题的时候要牢记sa和height数组的原理和作用！！！
 */

const int maxlen = 100 * 1005;

char s[maxlen];
int sa[maxlen], t[maxlen], t2[maxlen], c[maxlen];
int rankv[maxlen], height[maxlen];

//构造字符串s的后缀数组，每个字符值必须为0..m-1
int build_sa(int n, int m){
    int i, *x = t, *y = t2;

    //先构造第一轮的sa和x，K=1
    for(i = 0; i < m; i++)  c[i] = 0;
    for(i = 0; i < n; i++)  c[x[i] = s[i]]++;   //第一轮的x[i]并不是从0开始编号
    for(i = 1; i < m; i++)  c[i] += c[i-1];
    for(i = n-1; i >= 0; i--){
        sa[--c[x[i]]] = i;
    }

    for(int k = 1; k <= n; k <<= 1){
        int p = 0;

        //利用后缀数组sa[i]构造y[i]
        for(i = n-k; i < n; i++)
            y[p++] = i;     //后K个位置没有第二关键字，排序最高
        for(i = 0; i < n; i++){
            if(sa[i] >= k)  //前K个位置的第一关键字不构成第二关键字，因此y[i]的排序只跟sa[i]的位置K以后的相关
                y[p++] = sa[i]-k;
        }

        //基数排序，以第二关键字的排序为基准对第一关键字进行排序
        for(i = 0; i < m; i++)  c[i] = 0;
        for(i = 0; i < n; i++)  c[x[y[i]]]++;
        for(i = 1; i < m; i++)  c[i] += c[i-1];
        for(i = n-1; i >= 0; i--){
            sa[--c[x[y[i]]]] = y[i];    //稳定排序，即使x[i]第一关键字相同，但是y[i]较大的仍然排在后面
        }

        //根据sa和y数组计算新的各位置排名数组x[i]
        swap(x, y);
        p = 1;  //p表示不同名次的个数
        x[sa[0]] = 0;   //排名从0开始

        for(i = 1; i < n; i++){     
            //若sa[i]和sa[i-1]的第一关键字和第二关键字相同，则名次一样
            //这里不需要担心y[sa[i]+k]的数组越界，因为y[sa[i]]==y[sa[i-1]]表明后缀sa[i]和后缀sa[i-1]长度为k的后缀相同
            //若其中一个包含结束字符则必然不可能相等，因此sa[i]+k和sa[i-1]+k都必然<=n
            x[sa[i]] = y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k] ?  
                p-1 : p++;
        }

        if(p >= n) break;   //以后即使倍增后缀长度K，sa也不会改变，退出
        m = p;      //下次基数排序的最大值
    }

}

/* 判断模板pattern是否为后缀p的前缀，m为模板长度 */
int cmp_suffix(char* pattern, int m, int p){
    return strncmp(pattern, s+sa[p], m);
}

/* 查找模板P在文本串s中的位置，n为文本串长度 */
int find(char *P, int n){
    int m = strlen(P);
    if(cmp_suffix(P, m, 0) < 0) return -1;
    if(cmp_suffix(P, m, n-1) > 0) return -1;
    int L = 0, R = n-1;
    while(L <= R){  //对后缀数组进行二分查找，由于后缀数组是字典序排序的
        int M = L + (R-L)/2;
        int res = cmp_suffix(P, m, M);
        if(res == 0)    //匹配成功
            return M;
        if(res < 0)
            R = M-1;
        else 
            L = M + 1;
    }
    return -1;
}

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
        while(s[i+k] == s[j+k]) k++;
        height[rankv[i]] = k;
    }
}

int main(){
    int n;
    strcpy(s, "aabaaaab");    
    n = strlen(s);
    build_sa(n, 127);
    getHeight(n);
    for(int i = 0; i < n; i++){
        printf("%d\t", height[i]);
    }
    printf("\n");
    return 0;
}
