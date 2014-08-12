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
            _combine(num, idx+1, target-num[idx], vis, ret);
            vis.pop_back();

            _combine(num, idx+1, target, vis, ret);
        }

        vector<vector<int> > combinationSum2(vector<int> &num, int target){
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
    vector<int> num{14,6,25,9,30,20,33,34,28,30,16,12,31,9,9,12,34,16,25,32,8,7,30,12,33,20,21,29,24,17,27,34,11,17,30,6,32,21,27,17,16,8,24,12,12,28,11,33,10,32,22,13,34,18,12};
    auto res = s.combinationSum2(num, 27);
    for(auto vec : res){
        for(auto x : vec)
            cout << x << '\t';
        cout << endl;
    }
    return 0;
}
