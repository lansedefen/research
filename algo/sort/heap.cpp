#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

void InsertHeapElement(vector<int>& heap, int value) {
    heap.push_back(value);
    int i = heap.size();
    cout << i << endl;
    while(i >0) {
       if ((i-1)/2 > 0 && heap[i] < heap[(i-1)/2]) {
           int tmp = heap[i];
           heap[i] = heap[(i-1)/2];
           heap[(i-1)/2] = tmp;
       }
       i = (i-1)/2;
    }
}

int DeleteHeap(vector<int>& heap) {
    int value = heap[0];
    heap[0] = value;
    heap.pop();

    int i = heap.size();
    cout << i << endl;
    while(i >0) {
       if ((i-1)/2 > 0 && heap[i] < heap[(i-1)/2]) {
           int tmp = heap[i];
           heap[i] = heap[(i-1)/2];
           heap[(i-1)/2] = tmp;
       }
       i = (i-1)/2;
    }
    return value;
}

void adjust(vector<int>& heap, int index, int value) {
      int len = heap.size();
      heap[index] = value;
      int i = index;
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
         i = min_index;
      }
}

void build(vector<int>& heap) {
   int len = heap.size();
    for (int i = len/2; i--; i>=0) {
        adjust(heap, i, heap[i]);
    }
}

int main() {
    //1 build nlog(n)
    /* 
    vector<int> heap;
    insert(heap, 1);
    insert(heap, 3);
    insert(heap, 6);
    insert(heap, 8);
    cout << "----" << endl;
    for (int i=0; i< heap.size(); i++) {
        cout << heap[i] << endl;
    }
    */

    // 2 build log(n)
    vector<int> heap;
    heap.push_back(3);
    heap.push_back(6);
    heap.push_back(1);
    heap.push_back(8);
    build(heap); 
    cout << "----" << endl;
    for (int i=0; i< heap.size(); i++) {
        cout << heap[i] << endl;
    }

    cout << "----" << endl;
    adjust(heap,0, 4);
    for (int i=0; i< heap.size(); i++) {
        cout << heap[i] << endl;
    }

    return -1;
}
