#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    public:
        vector<string> ret;
        vector<vector<int> > d;
        string vis;

        bool _restoreIp(string &s, int idx, int nPart){
            if(d[idx][nPart] == 0){
                return d[idx][nPart] = false;
            }
            if(nPart < 0 || (nPart == 0 && idx < s.size()) ||
               (idx == s.size() && nPart > 0))
                return d[idx][nPart] = false;
            if(nPart == 0 && s.size() == idx){
                ret.push_back(vis);
                return d[idx][nPart] = true;
            }
            bool canRestore = false;
            for(int i = idx, num = 0; i < s.size(); i++){
                num = num * 10 + (s[i] - '0'); 
                if(num > 255 || (s[idx] == '0' && i != idx))
                    break;
                string num_str = to_string(num);
                if(nPart > 1)
                    num_str += '.';
                vis += num_str;
                if(_restoreIp(s, i+1, nPart-1)){
                    canRestore = true;
                }
                vis.erase(vis.end()-num_str.size(), vis.end());
            }
            return d[idx][nPart] = canRestore;
        }

        vector<string> restoreIpAddresses(string s){
            d = vector<vector<int> >(s.size()+1, vector<int>(5, -1)); 
            _restoreIp(s, 0, 4);
            return ret;
        }
};

int main(){
    Solution s; 
    vector<string> ret = s.restoreIpAddresses("010010");
    for(auto &s : ret){
        cout << s << endl;
    }
    return 0;
}
