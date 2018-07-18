#ifndef REMOVE_LIST_H_                                                
#define REOMOVE_LIST_H_ 


#include<iostream>
#include<vector>
#include"list_head.h"

using namespace std;

void move(ListNode* &p) {
    p = p->next;
}

void RemoveNode(ListNode* &p, int value) {
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
    /*ListNode* index = start;
    int base = start->value;
    while(start != end) {
        if(start->value < value) {
            
        }

        cout << start-> value << ", ";
        start = start->next;
    }*/
    return start;
}

#endif
