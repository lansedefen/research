#ifndef REMOVE_LIST_H_                                                
#define REOMOVE_LIST_H_ 


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

ListNode* PartList(ListNode* start, ListNode* end) {
    ListNode* index = start;
    int base = start->value;

    ListNode* smaller = NULL;
    ListNode* bigger = NULL;
    while(start != end) {
        ListNode* q = start;
        start = start -> next;

        if(q->value <= base) {
            q->next = smaller;
            smaller = q;
        } else {
            q->next = bigger;
            bigger = q;
        }
        //cout << start-> value << ", ";
    }

    index ->next = bigger;
    return smaller;
}

#endif
