#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

typedef list<int> LISTINT;

void adjust(vector<int>& heap, int value) {
      int len = heap.size();
      heap[0] = value;
      int i = 0;
      while (i<len) {  
         int min_index = i;
         // 先和左子树比较，获取较小值
         if(2*i + 1 < len) {
             if(heap[i] > heap[2*i +1]) {
                 min_index = 2*i +1;
             }
         } 

         // 右边
         if(2*i +2 < len) { // 
             if(heap[min_index] > heap[2*i +2]) {
                min_index = 2*i +2;
             }
         }

         if (min_index == i) {
             return;
         }

         int tmp = heap[min_index];
         heap[min_index] = heap[i];
         heap[i] = tmp;
         i = min_index
      }
}

int main()
{
    vector<LISTINT::iterator> list_iterator_array;
    vector<LISTINT*> list_array;
    LISTINT listone;
    listone.push_back (1);
    listone.push_back (4);
    listone.push_back (9);
    listone.push_back (15);
    LISTINT::iterator one = listone.begin();
    list_iterator_array.push_back(one);
    list_array.push_back(&listone);

    LISTINT listtwo;
    listtwo.push_back (-1);
    listtwo.push_back (2);
    listtwo.push_back (3);
    listtwo.push_back (8);
    LISTINT::iterator two = listtwo.begin();
    list_iterator_array.push_back(two);
    list_array.push_back(&listtwo);

    LISTINT listthree;
    listthree.push_back (-1);
    listthree.push_back (-2);
    listthree.push_back (-3);
    listthree.push_back (7);
    listthree.push_back (17);
    listthree.push_back (19);
    LISTINT::iterator three = listthree.begin();
    list_iterator_array.push_back(three);
    list_array.push_back(&listthree);

    //
    bool flag;
    vector<int> tmp;
    tmp.push_back(1);
    tmp.push_back(-1);
    tmp.push_back(-1);

    int count =1;
    while(1) {
        flag = true;
        count +=1;
        for(int i = 0; i < list_iterator_array.size(); i++ ) {
            if (list_iterator_array[i] != (*list_array[i]).end()) {
                flag = false;
            }
        }
        if(flag) break;
        //if(count >15) break;
        
        vector<int>::iterator maxPosition = min_element(tmp.begin(), tmp.end());
        int index = maxPosition - tmp.begin();
        cout << "maxvalue:" << *maxPosition << " max index: " << index <<endl;
        list_iterator_array[index] ++;
        tmp[index] = *list_iterator_array[index];
    }
    return -1;
}

