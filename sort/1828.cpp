#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>

using namespace std;

struct point {
    int x, y;
};

point monkeys[50000];

int cmp_point_y(const void *a, const void *b){
    point *pa = (point*)a;
    point *pb = (point*)b;

    if((pa->y > pb->y) || (pa->y == pb->y && pa->x > pb->x)){
        return -1;
    }else{
        return 1;
    }
}

int main(){
    int N;

    for(;;){
        scanf("%d", &N);
        if(N == 0)
            break;

        for(int i = 0; i < N; i++)
            //cin >> monkeys[i].x >> monkeys[i].y超时
            scanf("%d%d", &monkeys[i].x, &monkeys[i].y);

        qsort(monkeys, N, sizeof(point), cmp_point_y);

        int max_x = INT_MIN, num_king = 0, cur_y = INT_MIN;

        for(int i = 0; i < N; i++){
            if(monkeys[i].y != cur_y){
                if(monkeys[i].x > max_x){
                    num_king++;
                    max_x = monkeys[i].x;
                }
                cur_y = monkeys[i].y;
            }
        }

        cout << num_king << endl;
    }

    return 0;
}
