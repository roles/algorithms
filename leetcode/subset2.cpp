#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    public:
        void _subset(vector<int> &s, int idx, vector<int> &vis,
                vector<vector<int> > &ret){
            if(idx == s.size()){
                ret.push_back(vis);
                return;
            }
            int k = idx;
            while(k < s.size() && s[k] == s[idx])
                k++;

            _subset(s, k, vis, ret);

            for(int i = idx; i < k; i++){
                vis.push_back(s[i]);
                _subset(s, k, vis, ret);
            }

            for(int i = idx; i < k; i++)
                vis.pop_back();
        }

        vector<vector<int> > subsetsWithDup(vector<int> &S){
            sort(S.begin(), S.end());
            vector<vector<int> > ret;
            vector<int> vis;

            _subset(S, 0, vis, ret);

            return ret;
        }
};

int main(){
    Solution s; 
    vector<int> a{1,2,2};
    
    vector<vector<int> > ret = s.subsetsWithDup(a);
    for(auto vec : ret){
        for(auto x : vec)
            cout << x << '\t';
        cout << endl;
    }
    return 0;
}
