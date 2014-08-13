#include <iostream>
#include <vector>

using namespace std;

/*
 * 原题的意思是全部正数中第一个没有在这个数组出现的正数
 * 解法是将每个正数放到其对应下标的位置中
 */

class Solution {
    public:
        int firstMissingPositive(int A[], int n){
            if(n == 0)
                return 1;
            for(int i = 0; i < n; i++){
                int u = A[i], k = i;
                while(u > 0 && u <= n && u != k+1){
                    int tmp = A[u-1]; 
                    A[u-1] = A[k];
                    A[k] = tmp;
                    if(A[u-1] == A[k])
                        break;
                    u = tmp;
                }
            }

            for(int i = 0; i < n; i++){
                if(A[i] != i+1){
                    return i+1;
                }
            }
            return n+1;
        }
};

int main(){
    Solution s; 
    int A[] = {1,1,1,1}; 
    cout << s.firstMissingPositive(A, 4) << endl;
    return 0;
}
