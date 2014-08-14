#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        int canCompleteCircuit(vector<int> &gas, vector<int> &cost){
            int n = gas.size();
            for(int i = 0; i < n; i++){
                gas[i] = gas[i] - cost[i]; 
            }

            for(int k = 0; k < n; k++){
                if(gas[k] >= 0){
                    bool complete = true;
                    for(int i = 0, u = k, s = 0; i < n; i++){
                        s += gas[u];
                        u = (u+1) % n;
                        if(s < 0){
                            complete = false;
                            break;
                        }
                    }
                    if(complete)
                        return k;
                }
            }
            return -1;
        }
};

int main(){
    Solution s; 
    vector<int> gas{4,7,3,10}, costs{5,6,5,6};
    cout << s.canCompleteCircuit(gas, costs) << endl;
    return 0;
}
