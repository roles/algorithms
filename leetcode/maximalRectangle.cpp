#include <iostream>
#include <vector>

using namespace std;

/*
 * 动态规划
 */

class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        int nRows = matrix.size();
        if(nRows == 0)
            return 0;
        int nCols = matrix[0].size();
        if(nCols == 0)
            return 0;

        vector<int> colUpMax(nCols);
        vector<int> d(nCols);
        for(int i = 0; i < nCols; i++){
            colUpMax[i] = 0;
            d[i] = 0;
        }

        for(int i = 0; i < nRows; i++){
            int rowRightMax = 0;
            for(int j = 0; j < nCols; j++){
                if(matrix[i][j] == '1'){
                    rowRightMax++;
                    colUpMax[j]++;
                }else{
                    rowRightMax = 0;
                    colUpMax[j] = 0;
                }
                int iMax = d[j];
                if(j > 0){
                    iMax = iMax > d[j-1] ? iMax : d[j-1];
                }
                int subarea = 0;
                for(int k = 0, maxcol = colUpMax[j]; k < rowRightMax; k++){
                    maxcol = maxcol > colUpMax[j-k] ? colUpMax[j-k] : maxcol;
                    subarea = subarea < (maxcol * (k+1)) ? (maxcol * (k+1)) : subarea;
                }
                if(iMax < subarea){
                    iMax = subarea;
                }
                d[j] = iMax;
            }
        }

        int ret = d[nCols-1];
        return ret;
    }
};

int main(){
    vector<vector<char> > m = {
        {'1'}};
        /*
        {'0', '0', '0'}};
        {'1', '1', '0'},
        {'1', '1', '1'},
        {'0', '1', '1'},
        {'1', '1', '1'}};*/
    Solution s;
    cout << s.maximalRectangle(m) << endl;
    return 0;
}
