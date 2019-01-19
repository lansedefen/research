#include<iostream>
#include<vector>
#include"list_head.h"

using namespace std;

ListNode* ReverseList(ListNode* head) {
    ListNode* new_head = NULL;
    ListNode* tmp = NULL;
    while(head) {
        tmp = head;
        head = head->next;
        tmp -> next = new_head;
        new_head = tmp;
    }
    return new_head;
}

ListNode* SwapPairs(ListNode* head) {
	if (!head || !head -> next) return head;

	ListNode dummy(-1);
	dummy.next = head;

	ListNode* cur = &dummy;
	ListNode* p_next = cur->next;
	while(cur) {
		cout << cur ->value << endl;
		cur = cur ->next;
	}
	return head;
}

int main() {
    int a[5] = {1,2,3,4,5};
    vector<int> input_array(a, a+4);
    ListNode* head;
    CreateList(&head, input_array);
    PrintList(head);

    //ListNode* new_head = ReverseList(head);
    //PrintList(new_head);
	SwapPairs(head);
    return -1;    
}
