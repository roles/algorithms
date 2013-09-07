#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int m[65536];
int q[66000];

int is_sideup(int s){
    return (s == 0 || s == 65535);
}

int flip(int s, int pos){
    int d[] = {-1, 1, -4, 4}; 
    int i;
    s ^= 1 << pos; 
    for(i = 0; i < 4; i++){
        if(((abs(d[i]) == 1 && ((pos % 4) + d[i] < 0 || (pos % 4) + d[i] > 3))) || pos + d[i] < 0 || pos +d[i] > 15)
            continue;
        s ^= 1 << (pos + d[i]);
    }
    return s;
}

int main(){
    char c;
    int state, i, t, ns;
    int front, rear;
    int step;

    freopen("input.txt", "r", stdin);

    state = 0;
    memset(m, 0, sizeof(m));

    while(scanf("%c", &c) == 1){
        if('b' == c || 'w' == c){
            t = 'b' == c ? 1 : 0;
            state = (state << 1) | t;
        }
    }
    front = rear = 0;
    step = 0;
    if(is_sideup(state)){
        printf("%d\n", 0);
        return 0;
    }
    q[rear++] = state;
    q[rear++] = -1;
    while(front != rear){
        t = q[front++]; 
        if(t == -1){
            step++;
            if(front == rear)
                break;
            q[rear++] = -1;
            continue;
        }
        for(i = 0; i < 16; i++){
            ns = flip(t, i); 
            if(is_sideup(ns)){
                printf("%d\n", step + 1);
                return 0;
            }
            if(m[ns] == 0){
                q[rear++] = ns;    
                m[ns] = 1;
            }
        }
    }
    printf("Impossible\n");
     
    return 0;
}
