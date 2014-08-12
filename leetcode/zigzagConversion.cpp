#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int nRows){
        vector<string> rowStr(nRows);
        int idx = 0, col = 0;
        for(int i = 0; i < s.size(); i++){
            rowStr[idx].push_back(s[i]);
            if(col == 0 && idx < nRows-1){
                idx++;
            }else{
                col = (col+1) % nRows;
                idx = col;
            }
        }
        string res;
        for(int i = 0; i < nRows; i++)
            res += rowStr[i];
        return res;
    }
};

int main(){
    Solution s;
    cout << s.convert("ABCDE", 4) << endl;
    return 0;
}
