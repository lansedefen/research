#ifndef MOVE_LIST_H_                                                
#define MOVE_LIST_H_ 


#include<iostream>
#include<vector>
#include"list_head.h"

using namespace std;

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
