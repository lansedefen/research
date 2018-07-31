#include<vector>
#include"list_head.h"

ListNode* RotateList(ListNode* head, int n) {
    if(!head) return head;
 
    ListNode new_head = NULL;
    ListNode p = head;
    int i=0;
    while(!p && i< n-1) {
        new_head = p->next;
        p = p ->next;
        i++;
    }

    while(!p->next) {
        p = p -> next;
    }
    p->next = head;
    return new_head;
}
