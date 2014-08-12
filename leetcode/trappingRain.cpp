#include <iostream>
#include <vector>

using namespace std;

/*
 * 思路是先计算柱状图的凸包，再减去柱状图面积
 * 先找到最高的一个柱子，分左右两边计算凸包面积
 */

class Solution {
    public:
        int trap(int A[], int n) {
            if(n <= 2)
                return 0;
            int sum = 0, maxi = 0;
            for(int i = 0; i < n; i++){
                sum += A[i];
                if(A[i] > A[maxi]){
                    maxi = i;                     
                }
            }

            int left = 0;
            for(int k = 0, i = 0; i <= maxi; i++){
                if(A[i] > A[k]){
                    k = i; 
                }
                left += A[k];
            }

            int right = 0;
            for(int k = n-1, i = n-1; i >= maxi; i--){
                if(A[i] > A[k]){
                    k = i; 
                }
                right += A[k];
            }

            return left + right - A[maxi] - sum;
        }
};

int main(){
    Solution s; 
    int A[] = {0,2,1};
    cout << s.trap(A, 3) << endl;
    return 0;
}
