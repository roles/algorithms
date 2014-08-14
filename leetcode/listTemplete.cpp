#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
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
    ListNode* ptr = head;
    ptr = insertNode(ptr, 2);
    ptr = insertNode(ptr, 3);
    ptr = insertNode(ptr, 4);
    ptr = insertNode(ptr, 5);
    printList(head);

    Solution s;

    printList(head);

    deleteList(head);
    return 0;
}
