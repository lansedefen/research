#include <vector>  
#include <iostream>  
#include<queue>  
#include<set>  
#include <functional> // std::greater  
#include"list_head.h"

using namespace std;  
  
struct cmp {  
    bool operator()(ListNode* a, ListNode* b) {  
        return a->value > b->value;  
    }  
};  

//用一个大小为K的最小堆（用优先队列+自定义降序实现）(优先队列就是大顶堆，队头元素最大,自定义为降序后，就变成小顶堆，队头元素最小)，  
//先把K个链表的头结点放入堆中，每次取堆顶元素，然后将堆顶元素所在链表的下一个结点加入堆中。  
ListNode* MergeKList(vector<ListNode*> lists)  {  
    if (lists.size() == 0) 
		return NULL;  
    priority_queue<ListNode*, vector<ListNode*>, cmp> heap;  
    for (int i = 0; i < lists.size(); ++i)  {  
        heap.push(lists[i]);  
    }  
  
    ListNode* new_head, *p, *q;
	new_head = p = q = NULL;
    while (!heap.empty())  {  
        q = heap.top();  
        heap.pop();  
        if (q->next)    
            heap.push(q->next);

        if (!new_head) {   
            new_head = q;  
            p = q;  
        }  
        else  
        {  
            p->next = q;  
            p = p->next;  
        }  
    }  
    return new_head;  
}  

ListNode* Merge2List(ListNode* first_head, ListNode* second_head) {
	ListNode* new_head = NULL, *new_tail = NULL;
	while(first_head && second_head) {
        //cout << "first_head:" << first_head ->value << " ," << "second_head:" << second_head-> value << endl;
		if(first_head-> value < second_head -> value) {
			if( !new_head ) {
				new_head = first_head;
            } else {
			    new_tail->next = first_head;
			}

            new_tail = first_head;
			first_head = first_head->next;
		} else {
			if( !new_head) {
				new_head = second_head;
			} else {
			    new_tail->next = second_head;
            }

            new_tail = second_head;
			second_head = second_head->next;
		}
	}

    if (first_head == NULL) {
        new_tail->next = second_head;
    } else {
        new_tail->next = first_head;
    }
	return new_head;
}
  
int main()  {  
    vector<ListNode*> lists;  

    int array_1[] = {1,2,3,4,5};
    vector<int> input_array_1(array_1, array_1+5);
    ListNode* head_1;
    CreateList(&head_1, input_array_1);
    cout << "链表l1： ";  
    PrintList(head_1);

    int array_2[] = {2,4,6,7,9};
    vector<int> input_array_2(array_2, array_2+5);
    ListNode* head_2;
    CreateList(&head_2, input_array_2);
    cout << "链表l2： ";  
    PrintList(head_2);

    lists.push_back(head_1);  
    lists.push_back(head_2);  

    /*ListNode* res = MergeKList(lists);  
    cout << "合并后链表： ";  
    while (res) {  
        cout << res->value << " ";  
        res = res->next;  
    }  
    cout << endl;  
    */

    cout << "合并后链表： ";  
    ListNode* new_head = Merge2List(head_1, head_2);
    PrintList(new_head);
    return 0;  
}  
