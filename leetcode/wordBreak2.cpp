#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

/*
 * 动归，递归，剪枝
 */

using namespace std;

class Solution {
    public:
        bool _wordBreak(string &s, int idx, unordered_set<string> &dict,
                vector<int> &d, vector<string> &ret, string &vis){
            if(d[idx] == 0){
                return 0;
            }
            if(idx == s.size()){
                ret.push_back(vis);
                return 1;
            }
            for(int i = idx+1; i <= s.size(); i++){
                if(dict.find(string(s.begin()+idx, s.begin()+i)) != dict.end()
                    && d[i] != 0){

                    bool appendSpace = (vis.size() != 0);
                    if(appendSpace){
                        vis += ' ';
                    }
                    vis.append(s.begin()+idx, s.begin()+i);
                    d[i] = _wordBreak(s, i, dict, d, ret, vis); 
                    
                    if(appendSpace){
                        vis.erase(vis.end()-1, vis.end());
                    }
                    vis.erase(vis.end() - (i-idx), vis.end());

                    if(d[i] == 1){
                        d[idx] = 1; 
                    }
                }
            }
            if(d[idx] != 1)
                d[idx] = 0;
            return d[idx];
        }

        vector<string> wordBreak(string s, unordered_set<string> &dict) {
            vector<string> ret;
            int len = s.size();
            if(len == 0)
                return ret;
            vector<int> d(len+1, -1);
            d[len] = 1;
            string vis;
            _wordBreak(s, 0, dict, d, ret, vis);

            return ret;
        }
};

int main(){
    Solution s; 
    unordered_set<string> dict{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    //unordered_set<string> dict{"x"};
    for(auto str : s.wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", dict)){
        cout << str << endl;
    }
    return 0;
}
