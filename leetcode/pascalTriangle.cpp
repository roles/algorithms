#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        vector<vector<int> > generate(int numRows){
            vector<vector<int> > ret;
            if(numRows == 0)
                return ret;
            ret.push_back(vector<int>{1});
            for(int i = 1; i < numRows; i++){
                vector<int> vec(i+1, 0);
                for(int j = 0; j <= i; j++){
                    if(j-1 >= 0){
                        vec[j] += ret[i-1][j-1];
                    }
                    if(j < i){
                        vec[j] += ret[i-1][j];
                    }
                }
                ret.push_back(vec);
            }
            return ret;
        }
};

int main(){
    Solution s; 
    vector<vector<int> > ret = s.generate(5);
    for(auto& vec : ret){
        for(auto x : vec){
            cout << x << '\t';
        }
        cout << endl;
    }
    return 0;
}
