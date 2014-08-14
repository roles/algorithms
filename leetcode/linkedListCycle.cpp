#include <iostream>
#include <vector>

/*
 * 面对单向链表的题目，reverse list都是一个不错的思路
 *
 */

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        bool hasCycle(ListNode *head){
            if(head == NULL)
                return false;
            ListNode *cur = head->next, *pre = head;
            if(cur == NULL)
                return false;
            while(true){
                if(cur->next == NULL){
                    return false;
                }
                if(cur->next == head){
                    return true;
                }
                ListNode *nextPtr = cur->next;
                cur->next = pre;
                pre = cur;
                cur = nextPtr;
            }
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
    /*
    ptr = insertNode(ptr, 2);
    tmp = ptr = insertNode(ptr, 3);
    ptr = insertNode(ptr, 4);
    ptr = insertNode(ptr, 5);
    ptr->next = tmp;
    */

    Solution s;
    cout << s.hasCycle(head) << endl;

    //deleteList(head);
    return 0;
}
