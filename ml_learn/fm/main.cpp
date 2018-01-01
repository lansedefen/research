#include<iostream>
#include<vector>
#include "fm_model.h"

using namespace std;

int main() {
   fm_model* tmp = new fm_model();
   tmp->num_attribute = 3;
   tmp->num_factor = 2;
   cout << "k0:" << tmp->k0 << ", num_attribute:" << tmp->num_attribute  <<endl;
   cout << "k1:" << tmp->k1 <<endl;
   tmp->init();
   tmp->loadModel("./model_config");

   // 
   // 0:1.0, 1:0.2
   sparse_entry<FM_FLOAT>* tmp_data = new sparse_entry<FM_FLOAT>[2];
   tmp_data->id = 0;
   tmp_data->value = 1.0;
   (tmp_data + 1)->id = 0;
   (tmp_data + 1)->value = 1.0;

   sparse_row<FM_FLOAT> x;
   x.data = tmp_data;
   x.size = 2;
   cout << "predict:" << tmp->predict(x) << endl;
   return -1;
}
