#include <iostream>
#include <vector>

using namespace std;

void print_vec(vector<int> &num){
    for(int i = 0; i < num.size(); i++)
        cout << num[i] << '\t';
    cout << endl;
}

class Solution {
    public:

        void swap_ele(vector<int> &num, int i, int j){
            int tmp = num[i];
            num[i] = num[j];
            num[j] = tmp;
        }

        void _permute(vector<vector<int> > &res, vector<int> &num, int s){
            if(s >= num.size()-1){
                res.push_back(vector<int>(num));
                return;
            }
            for(int i = s; i < num.size(); i++){
                swap_ele(num, s, i);
                _permute(res, num, s + 1);
                swap_ele(num, s, i);
            }
        }

        vector<vector<int> > permute(vector<int> &num){
            vector<vector<int> > res;
            _permute(res, num, 0);
            return res;
        }
};

int main(){
    vector<int> num{1, 2, 3, 4, 5};
    Solution s;
    vector<vector<int> > res = s.permute(num);
    for(int i = 0; i < res.size(); i++){
        print_vec(res[i]); 
    }
    return 0; 
}
