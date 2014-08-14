#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

/*
 * 动态规划
 */

using namespace std;

class Solution {
    public:
        bool wordBreak(string s, unordered_set<string> &dict) {
            if(s.size() == 0)
                return false;
            int len = s.size();
            vector<bool> d(len, false); 
            for(int i = len - 1; i >= 0; i--){
                for(int j = i; j < len; j++){
                    if(dict.find(string(s.begin()+i, s.begin()+j+1)) != dict.end()){
                        if(j+1 < len){
                            if(d[j+1]){
                                d[i] = true;
                                break;
                            }
                        }else{
                            d[i] = true; 
                        }
                    }
                }
            }
            return d[0];
        }
};

int main(){
    Solution s; 
    unordered_set<string> dict{"e", "leet", "code"};
    cout << s.wordBreak("leete", dict) << endl;
    return 0;
}
