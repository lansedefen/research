#include <vector>  
#include <iostream>  
#include<queue>  
#include<set>  
#include <functional> // std::greater  

using namespace std;  
  
struct cmp  
{  
    bool operator()(ListNode* a, ListNode* b)  
    {  
        return a->val > b->val;  
    }  
};  

//方法一：利用最小堆方法  
//用一个大小为K的最小堆（用优先队列+自定义降序实现）(优先队列就是大顶堆，队头元素最大,自定义为降序后，就变成小顶堆，队头元素最小)，  
//先把K个链表的头结点放入堆中，每次取堆顶元素，然后将堆顶元素所在链表的下一个结点加入堆中。  
//
ListNode* mergeKLists2(vector<ListNode*> lists)  
{  
    if (lists.size() == 0) return NULL;  
    priority_queue<int, vector<ListNode*>, cmp> heap;  
    for (int i = 0; i < lists.size(); ++i)  
    {  
        heap.push(lists[i]);  
    }  
  
    ListNode* newHead=NULL;  
    ListNode* p=NULL;  
    ListNode* q=NULL;  
    while (!heap.empty())  
    {  
        q = heap.top();  
        heap.pop();  
        if (q->next != NULL)    
            heap.push(q->next);

        if (newHead == NULL) {   
            newHead = q;  
            p = q;  
        }  
        else  
        {  
            p->next = q;  
            p = p->next;  
        }  
    }  
    return newHead;  
}  
  
int main()  
{  
    vector<ListNode*> lists;  

    int array_1[5] = {1,2,3,4,5};
    vector<int> input_array_1(array_1, array_1+4);
    ListNode* head_1;
    CreateList(&head_1, input_array);
    cout << "链表l1： ";  
    PrintList(head_1);

    int array_2[5] = {2,4,6,7,9};
    vector<int> input_array_2(array_2, array_2+4);
    ListNode* head_2;
    CreateList(&head_2, input_array);
    cout << "链表l2： ";  
    PrintList(head_2);

    lists.push_back(head_1);  
    lists.push_back(head_2);  

    ListNode* res = mergeKLists2(lists);  
    cout << "合并后链表： ";  
    while (res) {  
        cout << res->val << " ";  
        res = res->next;  
    }  
    cout << endl;  
    DestroyList(res);  
    return 0;  
}  
