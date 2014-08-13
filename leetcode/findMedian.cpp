#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
    public:
        double _findMedian(int A[], int a1, int a2, 
                int B[], int b1, int b2){
            int m = a2 - a1, n = b2 - b1;
            int amid, bmid;
            if(m % 2 == 0){
                amid = a1 + m/2 - 1;
            }else{
                amid = a1 + m/2;
            }
            if(n % 2 == 0){
                bmid = b1 + n/2;
            }else{
                bmid = b1 + n/2;
            }

            if(m == 0){
                if(n % 2 == 0){
                    return (B[b1+n/2-1] + B[b1+n/2]) / 2.0;
                }else{
                    return B[b1+n/2];
                }
            }
            if(n == 0){
                if(m % 2 == 0){
                    return (A[a1+m/2-1] + A[a1+m/2]) / 2.0;
                }else{
                    return A[a1+m/2];
                }
            }
            if(n == 1 && m == 1){
                return (A[a1] + B[b1]) / 2.0;
            }

            if(A[amid] == B[bmid]){
                return A[amid]; 
            }else if(A[amid] < B[bmid]){
                if(amid == a1){
                    return _findMedian(
                        A, A[a1] > B[b1] ? a1 : a1+1, 
                        A[a2-1] > B[b2-1] ? a2-1 : a2,
                        B, A[a1] > B[b1] ? b1+1 : b1,
                        A[a2-1] > B[b2-1] ? b2 : b2-1);
                }else{
                    return _findMedian(A, amid, a2, B, b1, b2-(amid-a1)); 
                }
            }else{
                if(amid == a2-1){
                    if(A[amid] < B[b2-1]){
                        return _findMedian(A, a1, a2, B, b1+1, b2-1);
                    }else{
                        return _findMedian(A, a1+1, a2, B, b1+1, b2);
                    }
                }else{
                    return _findMedian(A, a1, amid+1, B, b1+(a2-amid-1), b2); 
                }

            }
        } 

        double findMedianSortedArrays(int A[], 
                int m, int B[], int n) {
            if(m <= n){
                return _findMedian(A, 0, m, B, 0, n);
            }else{
                return _findMedian(B, 0, n, A, 0, m);
            }
        }
};

int main(){
    Solution s; 
    int A[] = {1,2,2,2,10};
    int B[] = {3,3,3,3,3};
    cout << s.findMedianSortedArrays(A, 5, B, 5) << endl;
    return 0;
}
