#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        bool _isInterleave(string &s1, string &s2, string &s3,
                int idx1, int idx2, int idx3){
            bool left = false, right = false;
            if(idx3 == s3.size())
                return true;
            if(s1[idx1] == s3[idx3]){
                left = _isInterleave(s1, s2, s3, idx1+1, idx2, idx3+1);
            }
            if(s2[idx2] == s3[idx3]){
                right = _isInterleave(s1, s2, s3, idx1, idx2+1, idx3+1);
            }
            return left || right;
        }

        bool isInterleave(string s1, string s2, string s3) {
            if(s1.size() + s2.size() != s3.size())
                return false;
            return _isInterleave(s1, s2, s3, 0, 0, 0);
        }
};

int main(){
    Solution s; 
    cout << s.isInterleave("aabcc", "dbbca", "aadbbbaccc") << endl;
    return 0;
}
