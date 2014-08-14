#include <iostream>
#include <vector>

/*
 * 兔子每次跳两步，乌龟每次跳一步
 * 设从起点到循环的起点为x步，从循环起点到相遇点为m步，循环长度为y
 * 相遇时，(x+ty+m)*2 = x+ky+m，可知(k-2t)y = x + m，即(x+m)%y=0
 * 那么从相遇点再走x步必然构成一次循环，即回到循环起点
 */

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* detectCycle(ListNode* head){
            ListNode *slow = head, *fast = head; 
            do{
                if(slow == NULL || fast == NULL)
                    return NULL;
                slow = slow->next;
                fast = fast->next;
                if(fast == NULL)
                    return NULL;
                fast = fast->next;
            }while(slow != fast);

            slow = head;
            while(slow != fast){
                slow = slow->next; 
                fast = fast->next;
            }

            return slow;
        }
};

ListNode* insertNode(ListNode* tail, int x){
    ListNode* node = new ListNode(x);
    tail->next = node;
    return node;
}

void deleteList(ListNode* head){
    while(head != NULL){
        ListNode* ptr = head;
        head = head->next;
        delete ptr;
    }
}

void printList(ListNode* head){
    while(head != NULL){
        cout << head->val << '\t';
        head = head->next;
    }
    cout << endl;
}

int main(){
    ListNode* head = new ListNode(1);
    ListNode* ptr = head, *tmp;
    ptr = insertNode(ptr, 2);
    tmp = ptr = insertNode(ptr, 3);
    ptr = insertNode(ptr, 4);
    ptr = insertNode(ptr, 5);
    ptr->next = head;

    Solution s;
    cout << s.detectCycle(head)->val << endl;

    //deleteList(head);
    return 0;
}
