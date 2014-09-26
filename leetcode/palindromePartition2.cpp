#include <iostream>
#include <vector>

using namespace std;

/*
 * 这种情况的DP要写成递推（只需记录状态），否则容易超时
 */

class Solution {
    public:
        //判断是否回文
        bool isPalin(string &s, int b, int e){
            while(b < e){
                if(s[b] != s[e]){
                    return false;
                }
                b++;
                e--;
            }
            return 1;
        }

        int _partition(string &s, int idx,
                vector<int> &vis){
            if(idx == s.size()){
                return 0;
            }
            if(vis[idx] != -1){
                return vis[idx];
            }
            if(isPalin(s, idx, s.size()-1)){
                return vis[idx] = 0;
            }
            int imin = -1;
            for(int i = idx; i < s.size(); i++){
                if(isPalin(s, idx, i)){
                    int m;
                    if(i == s.size()-1){
                        m = 0;
                    }else{
                        m = 1;
                    }
                    m += _partition(s, i+1, vis);
                    if(imin == -1 || imin > m){
                        imin = m;
                    }
                }
            }
            return (vis[idx] = imin);
        }

        int minCut(string s){
            int n = s.size();
            if(n == 0){
                return 0;
            }
            if(isPalin(s, 0, s.size()-1)){
                return 0;
            }
            vector<int> vis(n, -1);

            return _partition(s, 0, vis);
        }
};

int main(){
    Solution s; 
    cout << s.minCut(string(100000,'a')) << endl;
    return 0;
}
