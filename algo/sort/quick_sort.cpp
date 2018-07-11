#include<iostream>
#include<vector>
#include"../array/array_head.h"
#include"../array/remove_dumplicate.h"
#include"../list/list_head.h"

using namespace std;

void QuickSort(vector<int>& arr, int start, int end) {
	if(start >= end -1) {
	   return;
	}

    int middle = PartVector(arr, start, end);
    cout << "middle:" << middle << ", start:" << start << ", end:" << end << endl;
	QuickSort(arr, start, middle);
	QuickSort(arr, middle + 1, end);
}

ListNode* PartList(ListNode* head, ListNode* start, ListNode* end) {
    int base = head->value;
    cout << "base:" << base << endl;

    /*
    start = head;
    end = left->next;
    while(right) {
        if(base >= right->data) {
            left = left->next;
            int tmp = right->data;
            right->data = left->data;
            left->data = tmp;
        }   
        right = right->next;
    }
    head->data = left->data;
    left->data = base;
*/
    return head;
}

void QuickSortList(ListNode* head, ListNode* start, ListNode* end) {
    if(head == NULL) {
        return;
    }
    ListNode* middle = PartList(head, start, end);
    QuickSortList(head, start, middle);
    
}

int main() {
    int tmp[] = {2, 2, -1, 10, 0, 3};
    vector<int > arr(tmp, tmp + 6);
    PrintVector(arr);

    QuickSort(arr, 0, arr.size());
    PrintVector(arr);
    return -1;
}
