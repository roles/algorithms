#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAXSTEP 250000

using namespace std;

struct point {
    int x, y;
    int idx;
};

point steps[MAXSTEP];

int cmp_point_horizontal(const void *a, const void *b){
    point *pa = (point*)a; 
    point *pb = (point*)b; 

    if(pa->y > pb->y){
        return 1;
    }else if(pa->y == pb->y && pa->x > pb->x){
        return 1;
    }

    return -1;
}

int cmp_point_vertical(const void *a, const void *b){
    point *pa = (point*)a; 
    point *pb = (point*)b; 

    if(pa->x > pb->x){
        return 1;
    }else if(pa->x == pb->x && pa->y > pb->y){
        return 1;
    }

    return -1;
}

int main(){
    int n;
    char d;

    cin >> n;

    int cur_x = 0, cur_y = 0;
    steps[0].x = 0;
    steps[0].y = 0;
    steps[0].idx = 0;
    getchar();
    for(int i = 1; i < n+1; i++){
        d = getchar(); 
        switch(d){
            case 'N':
                cur_y++;
                break;
            case 'S':
                cur_y--;
                break;
            case 'W':
                cur_x--;
                break;
            case 'E':
                cur_x++;
                break;
        }
        steps[i].x = cur_x;
        steps[i].y = cur_y;
        steps[i].idx = i;
    }

    int start, end, len = MAXSTEP;
    char dir;

    qsort(steps, n+1, sizeof(point), cmp_point_horizontal); 

    for(int i = 0; i < n; i++){
        if(steps[i].y == steps[i+1].y && abs(steps[i].idx-steps[i+1].idx) != 1){
            int cur_start, cur_end, cur_len;
            char cur_dir;
            if(steps[i].idx < steps[i+1].idx){
                cur_start = steps[i].idx;
                cur_end = steps[i+1].idx;
                cur_dir = steps[i].x > steps[i+1].x ? 'W' : 'E';
            }else{
                cur_start = steps[i+1].idx;
                cur_end = steps[i].idx;
                cur_dir = steps[i+1].x > steps[i].x ? 'W' : 'E';
            }
            cur_len = abs(steps[i].x - steps[i+1].x);

            if((cur_len < len) || 
                    ((cur_len == len) &&
                    ((cur_start < start) || ((cur_start == start) && (cur_end > end))))){
                start = cur_start;
                end = cur_end;
                len = cur_len;
                dir = cur_dir;
            }
        }
    }

    qsort(steps, n+1, sizeof(point), cmp_point_vertical); 

    for(int i = 0; i < n; i++){
        if(steps[i].x == steps[i+1].x && abs(steps[i].idx-steps[i+1].idx) != 1){
            int cur_start, cur_end, cur_len;
            char cur_dir;
            if(steps[i].idx < steps[i+1].idx){
                cur_start = steps[i].idx;
                cur_end = steps[i+1].idx;
                cur_dir = steps[i].y > steps[i+1].y ? 'S' : 'N';
            }else{
                cur_start = steps[i+1].idx;
                cur_end = steps[i].idx;
                cur_dir = steps[i+1].y > steps[i].y ? 'S' : 'N';
            }
            cur_len = abs(steps[i].y - steps[i+1].y);

            if((cur_len < len) || 
                    ((cur_len == len) &&
                    ((cur_start < start) || ((cur_start == start) && (cur_end > end))))){
                start = cur_start;
                end = cur_end;
                len = cur_len;
                dir = cur_dir;
            }
        }
    }

    cout << len << " " << start << " " << end << " " << dir << endl;

    return 0;
}
