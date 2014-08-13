#include <iostream>
#include <climits>

using namespace std;

class Solution {
    public:
        int atoi(const char *str){
            while(' ' == *str || '\t' == *str || '\n' == *str){
                str++;
            }
            if(*str == '\0')
                return 0;

            bool minus = false;
            if(*str == '-'){
                minus = !minus;
                str++;
            }else if(*str == '+'){
                str++;
            }
            if(*str > '9' || *str < '0')
                return 0;
            
            long long val = 0;
            while(*str <= '9' && *str >= '0'){
                val = val * 10 + (*str - '0');
                if(!minus && val > INT_MAX){
                    return INT_MAX;
                }
                if(minus && -val < INT_MIN){
                    return INT_MIN;
                }
                str++;
            }
            if(minus)
                val = -val;

            return val;
        }
};

int main(){
    Solution s;
    cout << s.atoi("  -565ad12") << endl;
    return 0;
}
