#include <iostream>
#include <vector>

/*
 * 将所有数字相加，且分别针对计算机的每一位
 * 每一位的和对3取余就是出现一次数字的那一位
 * 因为其他数字都出现了3次
 */

using namespace std;

class Solution {
    public:
        int singleNumber(int A[], int n){
            int bits;
            int res = 0;
            for(int i = 0; i < 32; i++){
                bits = 0;
                for(int j = 0; j < n; j++){
                    bits += ((A[j] >> i) & 1);
                }
                res |= ((bits % 3) << i);
            }
            return res;
        }
};

int main(){
    Solution s; 
    int A[] = {5,5,5,7,7,7,3};
    cout << s.singleNumber(A, 7) << endl;
    return 0;
}
