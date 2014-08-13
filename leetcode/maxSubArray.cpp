#include <iostream>
#include <vector>

/*
 * 动态规划
 */

using namespace std;

class Solution {
    public:
        int maxSubArray(int A[], int n){
            int rightMax = 0;
            for(int i = 0; i < n; i++){
                int u = A[i];
                if(i > 0){
                    if(rightMax+A[i] > A[i-1]){
                        A[i] = rightMax + A[i];
                    }else{
                        A[i] = A[i-1];
                    }
                }
                if(rightMax + u < 0){
                    rightMax = 0; 
                }else{
                    rightMax = rightMax + u;
                }
            }
            return A[n-1];
        }
};

int main(){
    int A[] = {-2,1,-3,4,-1,2,1,-5,4};
    //int A[] = {-2,1};
    Solution s; 
    cout << s.maxSubArray(A, 9) << endl; 
    return 0;
}
