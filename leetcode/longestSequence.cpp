#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
    public:
        int longestConsecutive(vector<int> &num){
            int n = num.size();
            map<int, int> vTable;
            map<int, int> aTable;
            for(int i = 0; i < n; i++){
                if(vTable.find(num[i]) != vTable.end())
                    continue;
            }
        }
};

int main(){
    Solution s; 
    
    return 0;
}
