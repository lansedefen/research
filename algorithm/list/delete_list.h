#ifndef DELETE_LIST_H_                                                
#define DELETE_LIST_H_ 


#include<iostream>
#include<vector>
#include"list_head.h"

using namespace std;

void move(ListNode* &p) {
    p = p->next;
}

void DeleteListNode(ListNode* &p, int value) {
    if (!p) {
        return;
    }

    if (p->value == value) {
        move(p);
        return;
    }

    ListNode* pre = p;
    while(pre->next) {
        if(pre->next->value == value ) {
                move(pre->next);
                continue;
        } 
        pre = pre->next;
    }
}

#endif
