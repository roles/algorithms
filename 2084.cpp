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
};

bigint f[101];

int main(){
    int N = 0, n;

    f[0] = 1;
    f[1] = 1;
    while(true){
        scanf("%d", &n);
        if(n == -1)
            break;

        if(N > n){
            f[n].print_bigint();
            printf("\n");
            continue;
        }

        for(int k = max(2, N + 1); k <= n; k++){
            for(int i = 0; i < k; i++){
                f[k] += f[k-1-i] * f[i];
            }
        }

        N = n;
        f[n].print_bigint();
        printf("\n");
    }
    
    return 0;
}
