#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
    public:
        void _combine(vector<int> &num, int idx, int target, 
                vector<int> &vis, set<vector<int> > &ret){
            // num[idx] > target 剪枝
            if(idx == num.size() || num[idx] > target)
                return;
            if(num[idx] == target){
                vis.push_back(num[idx]);
                ret.insert(vis);
                vis.pop_back();
                return;
            }
            vis.push_back(num[idx]);
            _combine(num, idx, target-num[idx], vis, ret);
            vis.pop_back();

            _combine(num, idx+1, target, vis, ret);
        }

        vector<vector<int> > combinationSum(vector<int> &num, int target){
            vector<vector<int> > ret;
            set<vector<int> > ret_set;
            vector<int> vis;
            if(num.size() == 0)
                return ret; 
            sort(num.begin(), num.end());
            _combine(num, 0, target, vis, ret_set);  
            ret.assign(ret_set.begin(), ret_set.end());

            return ret;
        }
};

int main(){
    Solution s; 
    vector<int> num{2,3,6,7};
    auto res = s.combinationSum(num, 7);
    for(auto vec : res){
        for(auto x : vec)
            cout << x << '\t';
        cout << endl;
    }
    return 0;
}
