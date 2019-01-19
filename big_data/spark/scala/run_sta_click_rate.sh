source ~/.bashrc

output_file_dt="20180729"
/usr/local/hadoop/bin/hadoop dfs -rmr /tmp/chengyun5/mid_click_rate_$output_file_dt

/usr/local/spark/bin/spark-submit \
--master yarn  \
--num-executors 60 \
--name chengyun5_sta_click_rate \
--driver-memory 10g \
--executor-memory 15g \
--executor-cores 4 \
sta_click_rate.py "/user/hbase/hive/warehouse/m_deep_query_click_table/dt=$output_file_dt/0000*" "/tmp/chengyun5/mid_click_rate_$output_file_dt" > /tmp/res_$output_file_dt

#sta_click_rate2.py "/user/hbase/hive/warehouse/m_deep_query_click_table/dt=20180729/00009*" "/tmp/chengyun5/mid_click_rate4" > /tmp/res

#get_join.py /tmp/chengyun5/test_frozen_uid_list.txt  /tmp/chengyun5/test_uid_bl_platform.txt > /tmp/ww
#/usr/local/spark/bin/spark-submit --master spark://10.75.57.21:7077  get_join.py /tmp/chengyun5/uid_bl_platform.txt  > /tmp/ww
#/usr/local/spark/bin/spark-submit  get_join.py /tmp/chengyun5/uid_bl_platform.txt  > /tmp/ww
