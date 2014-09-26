#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        void merge(int A[], int m, int B[], int n){
            int pa = m-1, pb = n-1, pc = m+n-1;
            while(pa >= 0 && pb >= 0){
                if(A[pa] > B[pb]){
                    A[pc] = A[pa];
                    pa--;
                }else{
                    A[pc] = B[pb];
                    pb--;
                }
                pc--;
            }
            while(pa >= 0){
                A[pc--] = A[pa--];
            }
            while(pb >= 0){
                A[pc--] = B[pb--];
            }
        }
};

int main(){
    Solution s; 
    int A[10] = {1,3,5,7,9}, B[5] = {2,4,6,8,10};
    s.merge(A, 5, B, 5);
    for(int i = 0; i < 10; i++){
        cout << A[i] << '\t';
    }
    cout << endl;
    return 0;
}
