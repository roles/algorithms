#include <iostream>
#include <cstring>

using namespace std;

const int maxlen = 1000;

//pi[q]记录模式串P[1..q]的最长前后缀长度k
//即P[1..k] == P[q-k+1..q]
int pi[maxlen];

void compute_prefix(const char*);
void kmp_match(const char *t, const char *p);
int kmp_max_match(const char *t, const char *p);

int kmp_max_match(const char *t, const char *p){
    int m = strlen(p);
    int n = strlen(t);

    compute_prefix(p);

    int q = 0;      //q表示已经成功匹配的字符数
    int max_match = 0;
    
    for(int i = 0; i < n; i++){

        while(q > 0 && p[q] != t[i])
            q = pi[q];
        if(p[q] == t[i])
            q++;
        if(q > max_match){
            max_match = q;
        }
    }
    return max_match;
}

void kmp_match(const char *t, const char *p){
    int m = strlen(p);
    int n = strlen(t);

    compute_prefix(p);

    int q = 0;      //q表示已经成功匹配的字符数
    
    //每一次循环结束，q都是代表第i个位置的最长匹配
    for(int i = 0; i < n; i++){

        //当下一个字符不匹配时，就回到最长前缀的下一个位置继续匹配
        //直到下一个字符可以匹配或者跳到起始位置
        while(q > 0 && p[q] != t[i])
            q = pi[q];
        if(p[q] == t[i])
            q++;
        if(q == m){
            cout << "pattern occurs with shift " << i-m+1 << endl;
            q = pi[q];
        }
    }
}

/*
 * 计算前缀相当与对自己做一次匹配
 */
void compute_prefix(const char *p){
    bzero(pi, sizeof(pi));
    int m = strlen(p);

    pi[0] = 0;
    int k = 0;      //k表示已经匹配的字符数

    //每一次循环结束，k都是代表第i个位置的最长匹配
    for(int i = 1; i < m; i++){

        //p[k]是模式串的下一个字符，p[i]是文本串的下一个字符
        //如果两者不匹配，则根据已经有k个字符匹配的信息，k则变为其真后缀最长前缀长度
        //p[i-1]是后缀的最后一个字符
        //p[k-1]则是前缀的最后一个字符
        while(k > 0 && p[k] != p[i])    
            k = pi[k];
        if(p[k] == p[i])
            k++; 
        //这里pi[i]得到的就是字符串p[1..i]的后缀与前缀最大匹配的字符数
        pi[i] = k;
    }
}

void test_compute_prefix(){
    char str[] = "ababaca";
    
    int len = strlen(str);
    compute_prefix(str);
    for(int i = 0; i < len; i++){
        cout << i << '\t';
    }
    cout << endl;
    for(int i = 0; i < len; i++){
        cout << pi[i] << '\t';
    }
    cout << endl;
}

void test_kmp_match(){
    char text[] = "abcabccabb";
    char pattern[] = "cabc";
    kmp_match(text, pattern);
}

void test_kmp_max_match(){
    char text[] = "abcabccabb";
    char pattern[] = "cakcdda";
    cout << "max match : " << kmp_max_match(text, pattern) << endl;
}

int main(){
    test_kmp_max_match();
    return 0;
}
