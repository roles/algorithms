#include <iostream>
#include <vector>
#include <deque>

/*
 * O(1)空间的解法是先将后半部分reverse，在向前半部分插入
 */

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        void reorderList(ListNode *head) {
            if(head == NULL)
                return;

            deque<ListNode*> q; 
            ListNode* cur = head;
            while(cur != NULL){
                q.push_back(cur); 
                cur = cur->next;
            }

            ListNode *front, *back = NULL;
            while(!q.empty()){
                front = q.front();
                q.pop_front();

                if(back != NULL){
                    back->next = front;
                }

                if(q.empty()){
                    front->next = NULL;
                    return;
                }else{
                    back = q.back();
                    q.pop_back();
                    front->next = back;
                }
            }
            back->next = NULL;
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
    ListNode* ptr = head;
    ptr = insertNode(ptr, 2);
    ptr = insertNode(ptr, 3);
    ptr = insertNode(ptr, 4);
    ptr = insertNode(ptr, 5);
    printList(head);

    Solution s;
    s.reorderList(head);
    printList(head);

    deleteList(head);
    return 0;
}
