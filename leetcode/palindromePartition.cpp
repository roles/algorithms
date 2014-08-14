#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        //判断是否回文
        bool isPalin(string &s, int b, int e,
                vector<vector<int> > &d){
            if(d[b][e] != -1)
                return d[b][e];
            while(b < e){
                if(s[b] != s[e]){
                    d[b][e] = 0;
                    return false;
                }
                b++;
                e--;
            }
            return (d[b][e] = 1);
        }

        void _partition(string &s, int idx,
                vector<vector<int> > &d,
                vector<string> &vis,
                vector<vector<string> > &ret){
            if(idx == s.size()){
                ret.push_back(vis);  
                return;
            }
            for(int i = idx; i < s.size(); i++){
                if(isPalin(s, idx, i, d)){
                    vis.push_back(string(s.begin()+idx, s.begin()+i+1));
                    _partition(s, i+1, d, vis, ret);
                    vis.pop_back();
                }
            }
        }

        vector<vector<string> > partition(string s){
            vector<vector<string> > ret;
            int n = s.size();
            if(n == 0){
                return ret;
            }
            vector<vector<int> > d;
            vector<string> vis;
            for(int i = 0; i < n; i++)
                d.push_back(vector<int>(n, -1));

            _partition(s, 0, d, vis, ret);
            return ret;
        }
};

int main(){
    Solution s; 
    vector<vector<string> > ret = s.partition("aabbc");
    for(auto vec : ret){
        for(auto str : vec){
            cout << str << '\t';
        }
        cout << endl;
    }
    return 0;
}
