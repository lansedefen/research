#include<iostream>
#include<vector>
#include"array_head.h"
#include"../list/list_head.h"

using namespace std;

int PartVector(vector<int>& arr, int start, int end) {
	int i = start, j = end;
	int base = arr[start];
	while(i < j) {
	    while (arr[j] >= base && i < j) {
	        j--;
	    }
	    arr[i] = arr[j];

        while (arr[i] < base && i < j) {
	        i++;
	    }
	    arr[j] = arr[i];
	}
	arr[i] = base;
    return i;
}

void QuickSort(vector<int>& arr, int start, int end) {
	if(start >= end) {
	   return;
	}

    int middle = PartVector(arr, start, end);
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

    QuickSort(arr, 0, arr.size() - 1);
    PrintVector(arr);
    return -1;
}
