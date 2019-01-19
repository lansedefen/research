#!/bin/bash
s_date=$1
source ~/.bashrc
#drop table m_label_table;
/data1/hadoop/apache-hive-1.2.1-bin/bin/hive -e "
set mapred.reduce.tasks = 50;
SET mapreduce.job.queuename=hive;

CREATE TABLE IF NOT EXISTS m_label_table(  
        mid string,  
        click_rate string
        ) partitioned by (dt string) 
        ROW FORMAT DELIMITED FIELDS TERMINATED BY '\t';

INSERT OVERWRITE TABLE m_label_table PARTITION ( dt= $s_date)
    select
            t1.mid as mid,
            (t1.deep_click_rate + t2.valid_click_rate)/2.0 as click_rate
    from
            (select 
                mid,
                deep_click_rate,
                deep_click_num,
                deep_show_num,
                deep_pro_num,
                deep_opp_num,
                deep_fmt_num,
                deep_cmt_num,
                deep_like_num
            from 
                m_deep_label_table
            where
                dt = '$s_date'
            ) t1
      join 
            (select 
                mid,
                valid_click_rate,
                valid_click_num,
                valid_show_num,
                valid_pro_num,
                valid_opp_num,
                valid_fmt_num,
                valid_cmt_num,
                valid_like_num
            from 
                m_valid_label_table
            where
                dt = '$s_date'
            ) t2
      on t1.mid = t2.mid;
"
