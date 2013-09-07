#include<stdio.h>
#include<string.h>

char str[101][51];
int cnt[26];
int sortedness[101], tmp[101];

int main(){

    int n, m, c, i, k;
    int cur, len;
    char j;

    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    c = 0;

    while(c < m){
        memset(cnt, 0, sizeof(cnt));     
        scanf("%s", str[c]);
        sortedness[c] = 0;
        for(i = n - 1; i >= 0; i--){
            sortedness[c] += cnt[str[c][i] - 'A'];
            for(j = str[c][i] + 1; j <= 'Z'; j++){
                cnt[j - 'A']++;      
            }
        }
        c++;
    }
    cur = len = 0;
    for(i = 0; i < m; i++){
        cur = len - 1;
        while(cur >= 0 && sortedness[i] < sortedness[tmp[cur]])
            cur--;
        cur++;
        for(k = len; k >= cur; k--){
            tmp[k] = tmp[k - 1];
        }
        tmp[cur] = i;
        len++;
    }
    for(i = 0; i < m; i++){
        printf("%s\n", str[tmp[i]]);
    }
    return 0;
}
