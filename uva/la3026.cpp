#include <cstdio>
#include <cstring>

using namespace std;

// 若f[i]=r，则表示状态i失配时跳转到状态r
// P[1...r] = P[i-r+1...i]
// aaaa bbbb cccc dddd
//               r    i
//      aaaa bbbb cccc dddd
//                    r    i
// 如上图，即bbbb cccc dddd = aaaa bbbb cccc
// 又aaaa = aaaa, bbbb = bbbb ...
// 可以推出 aaaa = bbbb = cccc = dddd 即P是周期为i-r的周期串
// 反之，(i-f[i])*k=i时，P为周期串

int f[1000005];
char P[1000005];

void getFail(char *P, int *f){
    int m = strlen(P);
    f[0] = 0;
    f[1] = 0;
    for(int i = 1; i < m; i++){
        int r = f[i];
        while(r && P[r] != P[i])
            r = f[r];
        f[i+1] = P[r] == P[i] ? r+1 : 0;
    }
}

int main(){
    int m, ncase = 0;
    while(true){
        scanf("%d", &m);
        if(!m)
            break;
        scanf("%s", P);
        getFail(P, f);
        printf("Test case #%d\n", ++ncase);
        for(int i = 2; i <= m; i++){
            if(f[i] > 0 && i % (i-f[i]) == 0){
                printf("%d %d\n", i, i / (i-f[i]));
            }
        }
        printf("\n");
    }
    return 0;
}
