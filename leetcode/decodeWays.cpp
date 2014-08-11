#include <iostream>
#include <vector>

using namespace std;

/*
 * 递推，递归会超时，注意0
 */

class Solution {
    public:
        int _decode2(string &s){
            int len = s.size();
            vector<int> d(len+1); 
            d[len] = 1;
            d[len-1] = s[len-1] != '0' ? 1 : 0;
            for(int i = len-2; i >= 0; i--){
                if(s[i] != '0'){
                    d[i] = d[i+1];
                }else{
                    d[i] = 0;
                }
                if(s[i] == '1' ||
                   s[i] == '2' && (s[i+1] <= '6' && s[i+1] >= '0')){
                    d[i] += d[i+2];
                }
            }
            return d[0];
        }

        int numDecodings(string s){
            if(s.size() == 0)
                return 0;
            return _decode2(s);    
        }
};

int main(){
    Solution s;
    cout << s.numDecodings("0") << endl;
    return 0;
}
