#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        vector<int> getRow(int rowIndex){
            if(rowIndex == 0)
                return vector<int>{1};
            int numRows = rowIndex+1;
            vector<int> ret(numRows, 0);
            ret[0] = 1;
            for(int i = 1; i < numRows; i++){
                for(int j = i; j >= 0; j--){
                    if(j > 0){
                        ret[j] += ret[j-1];
                    }
                }
            }
            return ret;
        }
};

int main(){
    Solution s; 
    vector<int> vec = s.getRow(3);
    for(auto x : vec){
        cout << x << '\t';
    }
    cout << endl;
    return 0;
}
