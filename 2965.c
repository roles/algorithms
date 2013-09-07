#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct state {
    int data;
    struct state *prev;
    int pos;
} state;

int m[65536];
state *q[65536];

state* switch_door(state *ps, int pos){
    state *pt;
    int i;
    pt = (state*)malloc(sizeof(state));
    pt->data = ps->data; 
    pt->prev = ps;
    pt->pos = pos;

    pt->data ^= (1 << pos);

    for(i = pos / 4 * 4; i < pos / 4 * 4 + 4; i++){
        pt->data ^= (1 << i);
    }

    for(i = pos % 4; i <= 15; i += 4){
        pt->data ^= (1 << i);
    }
    return pt;
}

void print_result(state *ps){
    int st[60000];
    int i;
    state *pt = ps;
    i = 0;
    st[i++] = ps->pos;
    while(pt->prev != NULL){
        pt = pt->prev;
        st[i++] = pt->pos;
    } 
    for(i = i - 2; i >= 0; i--){
        printf("%d %d\n", (15 - st[i]) / 4 + 1, (15 - st[i]) % 4 + 1);
    }
}

int main(){
    int i, t;
    char c;
    int s, step;
    int front, rear;
    state *ps, *pt;    

    freopen("input.txt", "r", stdin);
    memset(m, 0, sizeof(m));
    memset(q, 0, sizeof(q));

    s = 0;
    while(scanf("%c", &c) == 1){
        if('-' == c || '+' == c){
            t = '+' == c ? 0 : 1;                
            s = (s << 1) | t;
        }
    }
    front = rear = 0;
    step = 0;
    ps = (state*)malloc(sizeof(state));
    ps->prev = NULL;
    ps->data = s;
    ps->pos = -1;

    if(ps->data == 65535){
        printf("%d\n", 0);
        return 0;
    }
    q[rear++] = ps;
    q[rear++] = NULL;

    while(front != rear){
        ps =  q[front++];
        if(NULL == ps){
            step++;
            if(front == rear)
                break;
            q[rear++] = NULL;
            continue;
        }
        for(i = 15; i >= 0; i--){
            pt = switch_door(ps, i); 
            if(pt->data == 65535){
                printf("%d\n", step + 1);
                print_result(pt);
                return 0;
            }

            if(0 == m[pt->data]){
                q[rear++] = pt;
                m[pt->data] = 1;
            }
        }
    }
    printf("Impossible\n");
    return 0;
}
