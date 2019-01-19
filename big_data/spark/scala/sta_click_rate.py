from __future__ import print_function
import sys
import json
from collections import defaultdict
from pyspark.sql import SparkSession
import os

pic_action = ["54", "128", "749"]

def parse_showinfo(module):
        show_info = json.loads(module.strip())
        show_ids = []
        for v in show_info:
            cate = int(v.get("cate", -1))
            if cate in [31, 113, 10117, 10118, 26]:
                for k in v["info"]:
                    mid, stat_list = k.get("mid", "0"), k.get("stat", [-1, -1, -1])
                    if mid == "0" or stat_list == [-1, -1, -1] or type(stat_list) != list:
                        continue
                    stat_list.extend([0, 0])
                    show_ids.append((mid, stat_list))
        return show_ids

def getInverseIds(show_ids, click_ids):
        for k in show_ids:
            if k[0] in click_ids:
                k[1][3] += click_ids[k[0]][0]
                k[1][4] += click_ids[k[0]][1]
        show_ids.reverse()
        flag, valid_click_ids = False, []
        for k in show_ids:
            if flag == True:
                if k[1][3] == 0:
                    k[1][3] = -1
                    k[1][4] = -1
                valid_click_ids.append(k)
                continue

            if k[1][3] != 0:
                flag = True
                valid_click_ids.append(k)
        return valid_click_ids

def get_mid_data(line):
    try:
        key, kviter = line
        kviter = kviter.split("@@")
        click_ids,click_num = {},{}

        for k in kviter:
            item = k.split("$$")
            if item[2] in pic_action:
                item[2] = "749"
            tmp = click_ids.get(item[3], defaultdict(int))
            tmp[item[2]] += 1
            click_ids[item[3]] = tmp

        for mid in click_ids.keys():
            for act in click_ids[mid].keys():
                tmp = click_num.get(mid, [0, 0])
                if act != "749":
                    tmp[0] += 1
                    tmp[1] += click_ids[mid][act]
                    click_num[mid] = tmp
                elif act == "749":
                    if click_ids[mid][act] >= 3:
                        tmp[0] += 1
                        tmp[1] += 1
                        click_num[mid] = tmp

        module = item[1]
        show_ids = parse_showinfo(module)
        valid_click_ids = getInverseIds(show_ids, click_num)

        result = []
        if valid_click_ids != []:
            for k in valid_click_ids:
                #print(k[0], "\t", "\t".join([str(v) for v in k[1]]))
                res = k[1]
                res.insert(0, 1)
                result.append((k[0], res))
        return result
    except:
        return []

def append_result(x, y):
    res = []
    for first, second in zip(x, y):
        res.append(first + second)
    return res

def get_click_rate(x):
    try:
        tmp = x[1]
        tmp.insert(0, (x[1][4] + 0.0) / x[1][0])
        tmp.insert(0, x[0])
        return "\t".join([str(k) for k in tmp])
    except:
        return "-1\t-1"

mid_dict = {}
def map_data(line):
    try:
        if(len(line) !=2 ):
            return (line, -1)
        seq_id, info = line
        if seq_id is None or len(seq_id) < 10:
            return (line, -2)
        res = mid_dict.get(seq_id, 0)
        res +=1
        mid_dict[seq_id] = res
        if(res > 15):
            return (line, -3)
        else:
            return (line, 0)
    except:
        return (line, -4)

def check_data(x):
    if len(x) == 2 and (x[0] is not None and len(x[0]) >10) \
        and (x[1] is not None and len(x[1]) > 50 and len(x[1]) < 2000):
        return True
    else:
        return False

if __name__ == "__main__":
    # 0 config
    spark = SparkSession \
        .builder \
        .config("spark.default.parallelism", "400") \
        .appName("PythonJoin") \
        .getOrCreate()
    task_num = 800
    min_show_num = 40

    # 1 load data
    if len(sys.argv) >= 2:
        data_input_path = sys.argv[1]
    else:
        data_input_path = "/Users/wangchengyun/Downloads/aaa"

    if len(sys.argv) >= 3:
        data_output_path = sys.argv[2]
    else:
        data_output_path = "/tmp/bbb"

    click_show_join_rdd = spark.read.text(data_input_path).rdd.map(lambda r: r[0])
    
    """
    click_show_join_rdd = spark.read.text(data_input_path).rdd.map(lambda r: r[0])
    tmp = click_show_join_rdd.map(lambda x: x.split("\t")[0])
    for k in tmp.collect():
        print(k)
    """

    # 2 data process
    seq_mid_rdd = click_show_join_rdd.map(lambda x: (x.split("\t")[0], "$$".join(x.split("\t")))) \
        .filter(check_data) \
        .map(map_data).filter(lambda x: x[1] == 0).map(lambda x: x[0]) \
        .reduceByKey(lambda x, y: x + "@@" + y, task_num)

    #for k in seq_mid_rdd.take(100):
    #   print(k)

    mid_dict.clear()
    mid_click_rdd = seq_mid_rdd.map(lambda x: get_mid_data(x)) \
                    .filter(lambda x: len(x) > 0).flatMap(lambda x: x) \
                    .map(map_data).filter(lambda x: x[1] == 0).map(lambda x: x[0])
    #for item in mid_click_rdd.take(100):
    #    print (item)

    result_rdd = mid_click_rdd.reduceByKey(append_result, task_num)\
        .filter(lambda x: len(x) == 2 and x[1][0] > min_show_num)\
        .map(get_click_rate).coalesce(1, shuffle=True)

    # 3 save data
    if(not os.path.exists(data_output_path)):
        result_rdd.saveAsTextFile(data_output_path)

    # 4 debug info
    for k in result_rdd.take(100):
        print(k)

    spark.stop()
