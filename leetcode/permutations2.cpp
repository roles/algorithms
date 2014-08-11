#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

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
            set<int> m;
            for(int i = s; i < num.size(); i++){
                if(m.find(num[i]) != m.end()){
                    continue;
                }
                swap_ele(num, s, i);
                _permute(res, num, s + 1);
                swap_ele(num, s, i);
                m.insert(num[i]);
            }
        }

        vector<vector<int> > permuteUnique(vector<int> &num){
            sort(num.begin(), num.end());
            vector<vector<int> > res;
            _permute(res, num, 0);
            return res;
        }
};

int main(){
    vector<int> num{0, 1, 0, 0, 9};
    Solution s;
    vector<vector<int> > res = s.permuteUnique(num);
    for(int i = 0; i < res.size(); i++){
        print_vec(res[i]); 
    }
    return 0; 
}
