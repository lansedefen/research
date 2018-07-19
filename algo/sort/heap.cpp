#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <algorithm>
#include"../array/array_head.h" 

using namespace std;

void InsertHeap(vector<int>& heap, int value) {
    int i = heap.size();
    heap.push_back(value);

    while(i >0) {
       int father_index = (i-1)/2;
       if (father_index > 0 && heap[i] < heap[father_index]) {
            swap(heap[i], heap[father_index]);
       }
       i = father_index;
    }
}

void AdjustHeap(vector<int>& heap, int index, int value) {
      int len = heap.size();
      heap[index] = value;
      int i = index;
      while (i<len) {  
         int min_index = i;
         int left_index = 2*i+1;
         int right_index = 2*i+2;

         // 先和左子树比较，获取较小值
         if(left_index < len && heap[i] > heap[left_index]) {
                 min_index = left_index;
         } 
         // 右边
         if(right_index < len && heap[min_index] > heap[right_index]) {
                min_index = right_index;
         }

         if (i == min_index) {
            return;
         }
         swap(heap[i], heap[min_index]);
         i = min_index;
      }
}

int DeleteHeap(vector<int>& heap, int& value) {
    if (heap.size() == 0) {
        return -1;
    }

    value = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    AdjustHeap(heap, 0, value);
    return value;
}


void BuildHeap(vector<int>& heap) {
   int len = heap.size();
    for (int i = len/2; i--; i>=0) {
        AdjustHeap(heap, i, heap[i]);
    }
}

int main() {
    // 2 build log(n)
    vector<int> heap;
    heap.push_back(3);
    heap.push_back(6);
    heap.push_back(1);
    heap.push_back(8);
    BuildHeap(heap); 
    cout << "----" << endl;
    for (int i=0; i< heap.size(); i++) {
        cout << heap[i] << endl;
    }

    return -1;
}
