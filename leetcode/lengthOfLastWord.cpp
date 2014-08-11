#include <iostream>

using namespace std;

class Solution {
    public:
        int lengthOfLastWord(const char *s) {
            int len = 0;
            if(*s == '\0')
                return 0;
            while(*s != '\0'){
                if(*s != ' ')
                    len++;
                else{
                    if(s[1] != '\0' && s[1] != ' ')
                        len = 0;
                }
                s++;
            }
            return len;
        }
};

int main(){
    Solution s;
    cout << s.lengthOfLastWord("Hello    wrod    ") << endl;
    return 0;
}
