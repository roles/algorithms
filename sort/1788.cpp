/*
 * 1788 Building a New Depot
 * 题意：给定若干个拐点，求这些拐点构成的多边形边长
 * 解：分x和y两个方向求边的长度，以x方向的边为例，
 *     先将所有的点按先y后x排序，则排序后的序列
 *     每两个点在x方向上必然构成一条边（拐点）
 *
 */


#include <iostream>
#include <cstdlib>

using namespace std;

struct point {
    int x, y;
};

point posts[100000];

int cmp_point_y(const void *a, const void *b){
    point *pa = (point*)a;
    point *pb = (point*)b;

    if((pa->y > pb->y) || (pa->y == pb->y && pa->x > pb->x)){
        return 1;
    }else{
        return -1;
    }
}

int cmp_point_x(const void *a, const void *b){
    point *pa = (point*)a;
    point *pb = (point*)b;

    if((pa->x > pb->x) || (pa->x == pb->x && pa->y > pb->y)){
        return 1;
    }else{
        return -1;
    }
}

int main(){
    int P;

    while(true){
        cin >> P;
        if(P == 0)
            break;

        for(int i = 0; i < P; i++)
            cin >> posts[i].x >> posts[i].y;

        int len = 0;
        qsort(posts, P, sizeof(point), cmp_point_y);

        for(int i = 0; i < P; i+=2){
            len += abs(posts[i+1].x - posts[i].x);  
        }

        qsort(posts, P, sizeof(point), cmp_point_x);

        for(int i = 0; i < P; i+=2){
            len += abs(posts[i+1].y - posts[i].y);  
        }

        cout << "The length of the fence will be " << len << " units." << endl;
    }

    return 0;
}
