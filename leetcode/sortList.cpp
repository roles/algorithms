#include <iostream>

using namespace std;
    
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    /*
     * quicksort TLE
     * ptri总是指向比key小的最后一个元素的位置
     */
    ListNode* partition(ListNode *s, ListNode *e){
        int key = s->val;  
        ListNode* ptri = s;
        ListNode* ptrj = s->next;
        while(ptrj != e){
            if(ptrj->val < key){
                ptri = ptri->next;
                int tmp = ptri->val; 
                ptri->val = ptrj->val;
                ptrj->val = tmp;
            }
            ptrj = ptrj->next;
        }
        int tmp = s->val;
        s->val = ptri->val;
        ptri->val = tmp;
        return ptri;
    }

    void quicksort(ListNode *s, ListNode *e){
        if(s == e)
            return;
        ListNode *idx = partition(s, e);
        quicksort(s, idx);
        quicksort(idx->next, e);
    }

    /*
     * mergesort
     */
    ListNode* sortList(ListNode *head){
        //quicksort(head, NULL); 
        ListNode* ptr = head;
        int len = 0;
        while(ptr != NULL){
            len++;
            ptr = ptr->next;
        }
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
    ListNode* head = new ListNode(3);
    ListNode* ptr = head;
    ptr = insertNode(ptr, 4);
    ptr = insertNode(ptr, 2);
    ptr = insertNode(ptr, 5);
    ptr = insertNode(ptr, 1);
    printList(head);

    Solution s;
    head = s.sortList(head);
    printList(head);

    deleteList(head);
    return 0;
}
