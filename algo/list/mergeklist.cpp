#include <vector>  
#include <iostream>  
#include<queue>  
#include<set>  
#include <functional> // std::greater  

using namespace std;  
  
struct ListNode  
{  
    int val;  
    ListNode* next;  
};  
  
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
        if (q->next != NULL)    heap.push(q->next);  
        if (newHead == NULL)  
        {   
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
  
ListNode* CreateListNode(int value)  
{  
    ListNode* pNode = new ListNode();  
    pNode->val = value;  
    pNode->next = NULL;  
  
    return pNode;  
}  
  
void DestroyList(ListNode* pHead)  
{  
    ListNode* pNode = pHead;  
    while (pNode != NULL)  
    {  
        pHead = pHead->next;  
        delete pNode;  
        pNode = pHead;  
    }  
}  
  
void ConnectListNodes(ListNode* pCurrent, ListNode* pNext)  
{  
    if (pCurrent == NULL)  
    {  
    }  
    pCurrent->next = pNext;  
}  
  
  
  
int main()  
{  
    vector<ListNode*> lists;  
    ListNode* pNode1 = CreateListNode(1);  
    ListNode* pNode2 = CreateListNode(2);  
    ListNode* pNode3 = CreateListNode(3);  
    ListNode* pNode4 = CreateListNode(4);  
  
    ListNode* pNode5 = CreateListNode(2);  
    ListNode* pNode6 = CreateListNode(3);  
    ListNode* pNode7 = CreateListNode(4);  
    ListNode* pNode8 = CreateListNode(5);  
  
    ListNode* pNode9 = CreateListNode(6);  
    ListNode* pNode10 = CreateListNode(7);  
    ListNode* pNode11 = CreateListNode(8);  
    ListNode* pNode12 = CreateListNode(9);  
  
    ConnectListNodes(pNode1, pNode2);  
    ConnectListNodes(pNode2, pNode3);  
    ConnectListNodes(pNode3, pNode4);  
  
    ConnectListNodes(pNode5, pNode6);  
    ConnectListNodes(pNode6, pNode7);  
    ConnectListNodes(pNode7, pNode8);  
  
    ConnectListNodes(pNode9, pNode10);  
    ConnectListNodes(pNode10, pNode11);  
    ConnectListNodes(pNode11, pNode12);  
  
    ListNode* L1 = pNode1;  
    ListNode* L2 = pNode5;  
    ListNode* L3 = pNode9;  
    cout << "链表l1： ";  
    while (L1)  
    {  
        cout << L1->val << " ";  
        L1 = L1->next;  
    }  
    cout << endl;  
    cout << "链表l2： ";  
    while (L2)  
    {  
        cout << L2->val << " ";  
        L2 = L2->next;  
    }  
    cout << endl;  
  
    cout << "链表l3： ";  
    while (L3)  
    {  
        cout << L3->val << " ";  
        L3 = L3->next;  
    }  
    cout << endl;  
  
    lists.push_back(pNode1);  
    lists.push_back(pNode5);  
    lists.push_back(pNode9);  
    ListNode* res = mergeKLists2(lists);  
  
    cout << "合并后链表： ";  
    while (res)  
    {  
        cout << res->val << " ";  
        res = res->next;  
    }  
    cout << endl;  
    DestroyList(res);  
    return 0;  
}  
