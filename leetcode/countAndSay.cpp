#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
    public:
        string countAndSay(int n){
            string s("1");
            char scount[100];

            for(int i = 1; i < n; i++){
                string tmp;
                for(int j = 0; j < s.size(); j++){
                    char c = s[j];
                    int count = 1;
                    while(j+1 < s.size() && s[j+1] == c){
                        j++;
                        count++;
                    }
                    sprintf(scount, "%d", count);
                    tmp += scount;
                    tmp += c;
                }
                s = tmp;
            }

            return s;
        }
};

int main(){
    Solution s;
    cout << s.countAndSay(20) << endl;
    return 0;
}
