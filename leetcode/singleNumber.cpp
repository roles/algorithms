#include <iostream>
#include <vector>

/*
 * 异或运算的性质：（将异或看成没有进位的二进制加法）
 * 1. 交换律 a ^ b ^ c = a ^ c ^ b
 * 2. 结合律 a ^ b ^ c = a ^ (b ^ c)
 * 3. 0 ^ a = a,  a ^ a = 0
 */

using namespace std;

class Solution {
    public:
        int singleNumber(int A[], int n){
            int ret = 0;
            if(n == 0)
                return -1;
            for(int i = 0; i < n; i++){
                ret ^= A[i];
            }
            return ret;
        }
};

int main(){
    Solution s; 
    int A[] = {-1,-1,2,5,3,2,5};
    cout << s.singleNumber(A, 7) << endl;
    return 0;
}
