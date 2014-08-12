#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
    public:
        int jump(int A[], int n){
            queue<int> q;
            vector<int> vis(n, -1);
            if(n == 0)
                return 0;

            q.push(0);
            vis[0] = 0;
            while(!q.empty()){
                int u = q.front();
                q.pop();

                for(int k = A[u]; k >= -A[u]; k--){
                    int v = u + k;
                    if(v >= 0 && v < n && vis[v] == -1){
                        vis[v] = vis[u] + 1;
                        if(v == n-1)
                            return vis[n-1];
                        q.push(v);
                    }
                }
            }
            if(vis[n-1] != -1)
                return vis[n-1];
            else
                return 0;
        }
};

int main(){
    Solution s; 
    int A[] = {2,3,1,1,4};
    cout << s.jump(A, 5) << endl; 
    return 0;
}
