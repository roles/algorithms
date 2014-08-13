#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode *reverseBetween(ListNode *head, int m, int n){
            int i = 1;
            ListNode *cur = head, *pre = head;
            ListNode *p = NULL, *q = NULL;
            ListNode *first = NULL, *tail = NULL;
            if(m == n)
                return head;
            while(cur != NULL){
                if(i < m){
                    i++;
                    pre = cur;
                    cur = cur->next;
                }else if(i == m){
                    first = cur;
                    tail = cur;
                    p = pre;
                    i++;
                    pre = cur;
                    cur = cur->next;
                }else if(i < n){
                    ListNode* tmp = tail;
                    tail = cur;
                    cur = tail->next;
                    tail->next = tmp;
                    i++;
                }else if(i == n){
                    ListNode *tmp = tail;
                    q = cur->next; 
                    tail = cur; 
                    cur = cur->next;
                    tail->next = tmp;
                    i++;
                    break;
                }
            }

            if(m != 1){
                p->next = tail;
            }else{
                head = tail;
            }
            first->next = q; 
            return head;
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
    head = s.reverseBetween(head, 1, 1);
    
    printList(head);

    deleteList(head);
    return 0;
}
