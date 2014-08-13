#include <iostream>
#include <vector>
#include <string>

/*
 * 分治，保存中间结果，避免重复计算
 */

using namespace std;

class Solution {
    public:
        typedef string::iterator sIter;

        bool _isScarmble(sIter s1_begin, sIter s1_end, sIter s2_begin, sIter s2_end, int n){
            if(n == 1){
                return *s1_begin == *s2_begin;
            }
            for(int i = 1; i < n; i++){
                if(_isScarmble(s1_begin, s1_begin + i, s2_begin, s2_begin + i, i) &&
                   _isScarmble(s1_begin + i, s1_end, s2_begin + i, s2_end, n - i)){
                    return true;
                }
                if(_isScarmble(s1_begin, s1_begin + i, s2_begin + (n - i), s2_end, i) &&
                   _isScarmble(s1_begin + i, s1_end, s2_begin, s2_begin + (n - i), n - i)){
                    return true;
                }
            }
            return false;
        }

        bool _isScarmble(string &s1, string &s2, int s1_begin, int s1_end, int s2_begin, int s2_end, int n, vector<vector<vector<int> > > &d){
            if(d[s1_begin][s2_begin][n] != -1){
                return d[s1_begin][s2_begin][n];
            }
            if(n == 1){
                return d[s1_begin][s2_begin][n] = (s1[s1_begin] == s2[s2_begin]);
            }
            for(int i = 1; i < n; i++){
                if(_isScarmble(s1, s2, s1_begin, s1_begin + i, s2_begin, s2_begin + i, i, d) &&
                   _isScarmble(s1, s2, s1_begin + i, s1_end, s2_begin + i, s2_end, n - i, d)){
                    return d[s1_begin][s2_begin][n] = 1;
                }
                if(_isScarmble(s1, s2, s1_begin, s1_begin + i, s2_begin + (n - i), s2_end, i, d) &&
                   _isScarmble(s1, s2, s1_begin + i, s1_end, s2_begin, s2_begin + (n - i), n - i, d)){
                    return d[s1_begin][s2_begin][n] = true;
                }
            }
            return d[s1_begin][s2_begin][n] = false;
        }

        bool isScramble(string s1, string s2) {
            vector<vector<vector<int> > > d;
            int n = s1.size();
            for(int i = 0; i < n; i++){
                vector<vector<int> > t1;
                for(int j = 0; j < n; j++){
                    t1.push_back(vector<int>(n+1, -1));  
                }
                d.push_back(t1);
            }
            //return _isScarmble(s1.begin(), s1.end(), s2.begin(), s2.end(), s1.size());
            return _isScarmble(s1, s2, 0, n, 0, n, s1.size(), d);
        }
};

int main(){
    Solution s; 
    cout << s.isScramble("abcdefghijklmnopq", "efghijklmnopqcadb") << endl; 
    return 0;
}
