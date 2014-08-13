#include <iostream>
#include <vector>

using namespace std;

/*
 * one pass 基数排序
 * i指向0的最后一个位置，j指向1的最后一个位置
 * 每一个位置先通过v提取
 * 若碰到一个0，在0的最后一个位置写0（原来是1）
 * 在1的最后一个位置写1（原来是2）
 */

class Solution {
    public:
        void sortColors(int A[], int n){
            int i = -1, j = -1;
            for(int p = 0; p < n; p++){
                int v = A[p]; 

                A[p] = 2;

                if(v == 1){
                    A[++j] = 1;
                }else if(v == 0){
                    A[++j] = 1;
                    A[++i] = 0;
                }
            }
        }
};

int main(){
    Solution s; 
    
    return 0;
}
