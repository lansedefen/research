#!/bin/bash
source ~/.bashrc

start_time=`date "+%2Y-%m-%d %H:%M:%S"`
echo "start working time:" $start_time

run() {
    end_date=$1
    # 1 get data from hbase
    hbase_output_dir=/tmp/chengyun5/hbase_weibo/
    data_pre="weibo"
    echo $1
    #./get_from_hbase/get_base.sh $1 $end_date $hbase_output_dir $data_pre

    # 2 feature extract
    input_path=$hbase_output_dir${data_pre}_${1}_${end_date}
    output_path=/tmp/chengyun5/feature_weibo/wb_feature_${1}_${end_date}/
    echo "input_path: "$input_path
    echo "output_path: "$output_path
    ./main.sh  $input_path $output_path

    # 3 save hdfsdata to hive 
    /data1/hadoop/apache-hive-1.2.1-bin/bin/hive -e "
    CREATE TABLE IF NOT EXISTS m_feature_table(  
            mid string,  
            url string,
            content_feas string,
            user_feas string,
            source_feas string,
            word_feas string, 
            action_feas string,
            content string,
            seg_string string,
            q_score string
            ) partitioned by (dt string) 
            ROW FORMAT DELIMITED FIELDS TERMINATED BY '\t';

    load data inpath '$output_path' OVERWRITE into table m_feature_table partition(dt=$2);
    "
}

for i in `seq 0 5`
do
    base_date=20180331
    echo "basedate: "$base_date
    days=$i
    start_date=`date -d"$base_date +$days days" +"%Y-%m-%d"`
    dt_date=`date -d"$base_date +$days days" +"%Y%m%d"`
    echo "start_date: "$start_date"    "$dt_date
    run $start_date $dt_date
done

:<<!
!
