#include <iostream>
#include <vector>

using namespace std;

/*
 * 递归
 */

class Solution {
    public:
        vector<vector<int> > d;

        int _numDistinct(string &S, string &T, int s, int t){
            if(t == T.size()){
                return 1;
            }
            if(s == S.size()){
                return 0;
            }
            if(d[s][t] != -1){
                return d[s][t];
            }
            int di = _numDistinct(S, T, s+1, t);
            if(S[s] == T[t]){
                di += _numDistinct(S, T, s+1, t+1);
            }
            return d[s][t] = di;
        }

        int numDistinct(string S, string T){
            d = vector<vector<int> >(S.size(), vector<int>(T.size(), -1));
            return _numDistinct(S, T, 0, 0);
        }
};

int main(){
    Solution s; 
    cout << s.numDistinct("rabbbit", "rabbit") << endl;
    return 0;
}
