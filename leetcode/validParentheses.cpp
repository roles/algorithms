#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        typedef string::iterator sIter;

        bool isValid(string s) {
            if(s.size() == 0)
                return true;
            vector<char> sta; 
             
            sIter ptr = s.begin(); 
            while(ptr != s.end()){
                switch(*ptr){
                    case '(':
                    case '[':
                    case '{':
                        sta.push_back(*ptr);
                        break;
                    case ')':
                        if(sta.empty() || sta.back() != '('){
                            return false;
                        }
                        sta.pop_back();
                        break;
                    case ']':
                        if(sta.empty() || sta.back() != '['){
                            return false;
                        }
                        sta.pop_back();
                        break;
                    case '}':
                        if(sta.empty() || sta.back() != '{'){
                            return false;
                        }
                        sta.pop_back();
                        break;
                }
                ptr++;
            }
            if(sta.empty())
                return true;
            else
                return false;
        }
};

int main(){
    Solution s; 
    cout << s.isValid("([{}{}[]])") << endl; 
    return 0;
}
