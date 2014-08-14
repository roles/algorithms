#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        int candy(vector<int> &ratings){
            int n = ratings.size();
            vector<int> A(n, 1);

            for(int i = n-1; i > 0; i--){
                if(ratings[i] < ratings[i-1] && A[i] >= A[i-1]){
                    A[i-1] = A[i] + 1; 
                }else if(ratings[i] > ratings[i-1]){
                    int u = i;
                    while(ratings[u] > ratings[u-1]){ 
                        u--;
                    }
                    for(int j = u+1; j <= i; j++){
                        if(A[j] <= A[j-1]){
                            A[j] = A[j-1] + 1;
                        }
                    }
                    i = u + 1;
                }
            }
            int ret = 0;
            for(int i = 0; i < n; i++){
                ret += A[i];
            }
            return ret;
        }
};

int main(){
    Solution s; 
    vector<int> rates{2,1,4,3,2,4}; 
    cout << s.candy(rates) << endl;
    return 0;
}
