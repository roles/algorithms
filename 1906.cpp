/*
 * 1906 Three powers
 * 题意是用3的幂作为元素构成集合，将所有子集按子集的元素和排序
 * 由于第n个元素比前n-1个元素加起来都大，因此子集的选取跟二进制集合选取一致
 *
 */


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1000;

struct bigint {
    int len, s[maxn];

    bigint(){
        memset(s, 0, sizeof(s));
        len = 1;
    }

    bigint operator = (const int num){
        char num_str[maxn];

        sprintf(num_str, "%d", num);
        len = strlen(num_str);
        
        for(int i = 0; i < len; i++)
            s[len-1-i] = num_str[i] - '0';
    }

    bigint operator = (const bigint &a){
        memcpy(s, a.s, a.len * sizeof(int)); 
        len = a.len;
    }

    bigint operator + (const bigint &a) const {
        bigint b;
        b.len = 0;
        
        for(int i = 0, g = 0; g || i < max(len, a.len); i++){
            int x = g;
            if(i < len)
                x += s[i];
            if(i < a.len)
                x += a.s[i];
            b.s[b.len++] = x % 10;
            g = x / 10;
        }

        return b;
    }

    bigint operator += (const bigint &a) {
        *this = *this + a;
        return *this;
    }

    bigint operator * (const bigint &a) const {
        bigint b;
        b.len = 0;

        for(int i = 0; i < len; i++){
            for(int j = 0, g = 0; g || j < a.len; j++){
                int x = g + b.s[i+j];
                if(j < a.len)
                    x += s[i] * a.s[j];
                b.s[i+j] = x % 10;
                g = x / 10;
            }
        }
        
        if(b.s[len+a.len-1] == 0){
            b.len = len + a.len - 1;
        }else{
            b.len = len + a.len;
        }

        return b;
    }

    void print_bigint(){
        for(int i = len - 1; i >= 0; i--)
            printf("%d", s[i]);
    }
} tpow[65];

int main(){
    unsigned long long int N;
    int k = 0;
    tpow[0] = 1;
    bigint three;
    three = 3;

    while(true){
        scanf("%lld", &N);
        if(N == 0)
            break;

        N--;
        int pos = 0;

        printf("{");
        if(N == 0){
            printf(" }\n");
            continue;
        }
        while(N > 0){
            int x = N % 2;
            N = N / 2;
            if(x == 1){
                if(pos > k){
                    for(int i = k+1; i <= pos; i++){
                        tpow[i] = tpow[i-1] * three;
                    }
                    k = pos;
                }
                printf(" ");
                tpow[pos].print_bigint();
                if(N == 0){
                    printf(" }\n");
                }else{
                    printf(",");
                }
            }

            pos++;
        }
    }
    return 0;
}
