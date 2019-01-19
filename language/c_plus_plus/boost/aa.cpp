#include <stdio.h>
#include<iostream>

using namespace std;

int func(int n) {
         int sum=0,i;
         for(i=0; i<n; i++)
         {
                 sum+=i;
         }
         return sum;
}


int main() {
         int i;
         long result = 0;
         for(i=1; i<=100; i++)
         {
                 result += i;
         }

        int xx = func(10);
        cout << xx << ";"<< result << endl;
        return -1;
 }
