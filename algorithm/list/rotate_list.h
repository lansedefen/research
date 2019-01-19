#ifndef RETOTE_LIST_H_
#define RETOTE_LIST_H_

#include<vector>
#include"list_head.h"

ListNode* RotateList(ListNode* head, int n) {
    if(!head || n ==0) return head;
 
    ListNode* p = head;
    int len= 1;
    while(p->next) {
        p = p ->next;
        len++;
    }
	n = len - n % len;

	p->next = head; 
	int step = 0;
    while(step < n) {
        p = p -> next;
		step ++;
    }
    head = p->next;
	p->next = NULL;
    return head;
}


#endif
