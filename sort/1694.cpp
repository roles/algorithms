/*
 * 1694 An Old Stone Game 
 * 贪心，递归，排序
 * 
 */

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXLEN 200

struct node {
    int childs[MAXLEN];
    int child_num;
};

node T[MAXLEN];

int min_stone(int node_idx){

    if(T[node_idx].child_num == 0){
        return 1;
    }

    int *child_min_stone = new int[T[node_idx].child_num];
    for(int i = 0; i < T[node_idx].child_num; i++){
        child_min_stone[i] = min_stone(T[node_idx].childs[i]);
    }
    sort(child_min_stone, child_min_stone+T[node_idx].child_num, greater<int>());

    // sort the children stone, merge the top 2 by res1 + res2 - min(res1-k, res2)
    // k is kth merging step
    int res = child_min_stone[0];
    for(int i = 1; i < T[node_idx].child_num; i++){
        res = res + child_min_stone[i] - min(res-i, child_min_stone[i]);
    }
    delete[] child_min_stone;
    
    return res;
}

int main(){
    int m, n;
    cin >> m;

    while(m--){
        cin >> n;

        // read the tree
        for(int i = 0; i < n; i++){
            int node_idx;
            cin >> node_idx;

            cin >> T[node_idx].child_num;
            for(int j = 0; j < T[node_idx].child_num; j++)
                cin >> T[node_idx].childs[j];
        }
        
        cout << min_stone(1) << endl;
        
    }
    return 0;
}
