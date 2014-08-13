#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        int _bsearchLeft(int A[], int b, int e, int n, int target){
            int mid = b + n / 2; 
            if(n <=0 || (n == 1 && A[mid] != target)){
                return -1;
            }
            if(A[mid] == target){
                if(mid-1 >= b && A[mid-1] == target){
                    return _bsearchLeft(A, b, mid, mid-b, target);
                }else{
                    return mid;
                }
            }
            if(A[mid] > target){
                return _bsearchLeft(A, b, mid, mid-b, target);
            }else{
                return _bsearchLeft(A, mid+1, e, n-(mid-b+1), target);
            }
        }

        int _bsearchRight(int A[], int b, int e, int n, int target){
            int mid = b + n / 2; 
            if(n <= 0 || (n == 1 && A[mid] != target)){
                return -1;
            }
            if(A[mid] == target){
                if(mid+1 < e && A[mid+1] == target){
                    return _bsearchRight(A, mid+1, e, n-(mid-b+1), target);
                }else{
                    return mid;
                }
            }
            if(A[mid] > target){
                return _bsearchRight(A, b, mid, mid-b, target);
            }else{
                return _bsearchRight(A, mid+1, e, n-(mid-b+1), target);
            }
        }

        vector<int> searchRange(int A[], int n, int target){
            vector<int> ret;
            ret.push_back(_bsearchLeft(A, 0, n, n, target));
            ret.push_back(_bsearchRight(A, 0, n, n, target));
            return ret;
        }
};

int main(){
    Solution s; 
    int A[] = {5, 8, 8, 8, 8, 10};
    vector<int> ret = s.searchRange(A, 6, 8);
    cout << ret[0] << '\t' << ret[1] << endl; 
    return 0;
}
