#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        string getPermutation(int n, int k){
            if(n == 0)
                return "";
            string ret;

            vector<int> ex(n+1);
            ex[0] = 1;
            int e = 0;
            for(int i = 1; i <= n; i++){
                ex[i] = i * ex[i-1];
            }
            vector<char> num(n);

            for(int i = 0; i < n; i++){
                num[i] = '1' + i; 
            }

            e = n-1;
            for(int i = 0; i < n; i++){
                int a = (k-1) / ex[e] + 1;
                int b = k - (a-1) * ex[e];
                ret += num[a-1];
                num.erase(num.begin()+a-1);
                k = b;
                e--;
            }

            return ret;
        }
};

int main(){
    Solution s; 
    //cout << s.getPermutation(7, 45) << endl;
    cout << s.getPermutation(4, 17) << endl;
    return 0;
}
