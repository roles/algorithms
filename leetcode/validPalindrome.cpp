#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        char lower(char c){
            if(c >= 'A' && c <= 'Z'){
                return 'a' + c - 'A';
            }
            return c;
        }

        bool isValid(char c){
            return (c >= '0' && c <= '9') ||
                (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z');
        }
        
        bool isPalindrome(string s){
            if(s.size() == 0)
                return true;
            int front = 0, rear = s.size()-1;
            while(front < rear){
                while(!isValid(s[front]) && front < s.size()) 
                    front++;
                while(!isValid(s[rear]) && rear >= 0) 
                    rear--;
                if(front >= rear)
                    return true;
                if(lower(s[front]) != lower(s[rear])){
                    return false;
                }
                front++;
                rear--;
            }
            return true;
        }
};

int main(){
    Solution s; 
    cout << s.isPalindrome(".,") << endl;
    return 0;
}
