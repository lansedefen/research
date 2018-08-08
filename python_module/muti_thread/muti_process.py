#encoding=utf8
import sys
import json
import  requests
import multiprocessing
import time
import os
import random

reload(sys)
sys.setdefaultencoding('utf-8')

uid_dict = {}
write_obj = ""
num =0
start_time = time.time()

def get_weibo(mid):
    url = "http://10.75.57.27/getdata/querydata2.php?condition=%s&mode=weibo&format=json" % (mid.strip())
    try:
        return requests.get(url, timeout=4).text
    except:
        return None

def parse_weibo(text):
    if text is None:
        return
    weibo = json.loads(text)
    content = weibo.get("CONTENT", "0")
    pattern = weibo.get("PATTERN_RECOG_CONTENT", "0")
    quality_score = weibo.get("QUALITY_SCORE", "0")
    q_score = "0"
    if quality_score != "0":
        quality_json = json.loads(quality_score)
        q_score = quality_json.get("q_score", "0")

    qi = weibo.get("QI","0")
    time = weibo.get("TIME","0")
    uid = weibo.get("UID","0")
    url = weibo.get("URL","0")
    return url,pattern,qi,uid,time,content,q_score
    
def read_dict(uid_dic):
    with open("./sexu_user/sexu_user","r") as obj:
        for line in obj:
            uid_dic[line.strip()] = 1

def run(tupl):
        is_sq, is_sq_user,is_adv,is_active, is_poll,is_template = 0,0,0,0,0,0
        mid,dt,deep_rate = tupl

        text = get_weibo(mid)
        if text is None:
            return
        url,pattern,qi,uid,time,content,q_score = parse_weibo(text)
        
        if url is None:
            return
        #seqing
        if (int(pattern) & (1 << 1)) >> 1 == 1 or (int(pattern) & (1 << 2)) >> 2 == 1:
            is_sq = 1
        if (int(pattern) & 1) == 1:
            is_adv = 1
        if (int(pattern) & 1<<3) >> 3 == 1:
            is_active = 1
        if (int(pattern) & 1<<6) >> 6 == 1:
            is_poll = 1
        if (int(pattern) & 1<<5) >> 5 == 1:
            is_template = 1
        if uid in uid_dict.keys():
            is_sq_user = 1

        res = url.strip() +"\t" + mid.strip() + "\t" + deep_rate + "\t" + uid + "\t" + time + "\t" + dt + "\t" +  q_score +  "\t" + str(is_sq) + "\t" + str(is_sq_user) + "\t" + str(is_adv) + "\t" + str(is_active) + "\t" + str(is_poll) + "\t" + str(is_template) + "\t" + content
        return res 

def write_data(x):
    global num, start_time, write_obj
    num +=1
    if (num % 5000 ==0):
        finish_time = time.time()
        print "num:", num, "\t", "consume_time:", finish_time  - start_time
        start_time = finish_time
    if x is None:
        return
    write_obj.write(x + "\n")

if __name__ == "__main__":
    #read_dict(uid_dict)
    read_obj = open(sys.argv[1])
    write_obj = open(sys.argv[2], "w")
    pool = multiprocessing.Pool(processes = 10)

    for line in read_obj:
        line = line.strip()
        mid, dt, deep_rate = line.split("\t")[0].strip(), line.split("\t")[10].strip(), line.split("\t")[1].strip()
        i = (mid.strip(), dt.strip(), deep_rate.strip())
        pool.apply_async(run, (i, ), callback=write_data)   #维持执行的进程总数为processes，当一个进程执行完毕后会添加新的进程进去

    pool.close()
    pool.join()   #调用join之前，先调用close函数，否则会出错。执行完close后不会有新的进程加入到pool,join函数等待所有子进程结束
    print "Sub-process(es) done."
    print("total_time:", finish_time - start_time)
    read_obj.close()
    write_obj.close()
