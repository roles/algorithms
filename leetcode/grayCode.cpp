#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
    public:
        vector<int> d;
        vector<int> vis;

        int turnBit(int x, int i){
            int y = 1 << i;
            return x ^ y;
        }

        void _grayCode(int cur, int n, int num){
            vis.push_back(cur);
            d[cur] = 1;
            if(vis.size() == num){
                return;
            }
            for(int i = 0; i < n; i++){
                int nex = turnBit(cur, i);
                if(!d[nex]){
                    _grayCode(nex, n, num);
                    break;
                }
            }
        }

        vector<int> grayCode(int n){
            int num = static_cast<int>(pow(2, n));
            d = vector<int>(num, 0);
            vis.clear();
            _grayCode(0, n, num);
            return vis;
        }
};

int main(){
    Solution s; 
    vector<int> ret = s.grayCode(3);
    for(auto x : ret){
        cout << x << '\t';
    }
    cout << endl;
    return 0;
}
