#include <vector>
#include <iostream>

using namespace std;

class Solution {
    public:
        int minPathSum(vector<vector<int> > &grid){
            if(!grid.size())
                return 0;
            int nRows = grid.size();
            if(!grid[0].size())
                return 0;
            int nCols = grid[0].size();

            vector<int> d(nCols);
            for(int i = nRows-1; i >= 0; i--)
                for(int j = nCols-1; j >= 0; j--){
                    int iMin = d[j];
                    if(j < nCols-1){
                        if(i == nRows-1){
                            iMin = d[j+1];
                        }else{
                            iMin = iMin > d[j+1] ? d[j+1] : iMin;
                        }
                    }
                    d[j] = iMin + grid[i][j];
                }

            return d[0];
        }
};

int main(){
    vector<vector<int> > grid { 
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    Solution s;
    cout << s.minPathSum(grid) << endl;
    return 0;
}
