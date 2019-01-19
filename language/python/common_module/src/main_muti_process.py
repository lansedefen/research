# -*- coding: utf-8 -*-
from multiprocessing import Pool, Lock
from time import clock
import requests 

from create_logger import logger 
import extract_weibo

def mycallback(x):
    with open('../data/data.txt', 'a+') as f:
        f.writelines(str(x) + "\n")

def with_lock(text):
    lock.acquire()
    with open('request.log', 'a+') as logs:
        logs.write('request %s cost: %s\n' % (url, end_time - start_time))
    lock.release()

def init_lock(l):
	global lock
	lock = l

def get_weibo(mid):
    url = "http://10.75.57.27/getdata/querydata2.php?condition=%s&mode=weibo&format=json" % (mid.strip())
    #try:
    if 1:
        start_time = clock()
        text = requests.get(url, timeout=4).text 
        end_time = clock()
        cost_time = end_time - start_time 
        logger.debug("url:" + url + ", cost_time:" + str(cost_time))

        # do sth
        res = extract_weibo.parse_weibo(text)
        #print res 
        #with_lock(text)
        return text  
    #except:
    #    return None

def muti_process_with_map(file_name):
    core_num = 10
    data = []
    obj = open(file_name, "r")
    for line in obj:
        ele = line.strip().split("\t")[1]
        data.append(ele)
    obj.close()

    lock = Lock()
    pool = Pool(core_num, initializer = init, initargs=(lock,) )
    pool.map_async(get_weibo, data, callback = mycallback)
    pool.close()
    pool.join()
    return 

def muti_process_with_apply(file_name):
    core_num = 10
    lock = Lock()
    pool = Pool(core_num, initializer = init_lock, initargs=(lock,) )
    obj = open(file_name, "r")
    for line in obj:
        ele = line.strip().split("\t")[1]
        # debug single
        #get_weibo(ele)
        #pool.apply(get_weibo, (ele, ))
        pool.apply_async(get_weibo, (ele, ), callback = mycallback)
    pool.close()
    pool.join()
    return 

if __name__ == '__main__':
    e1 = clock()
    file_name = "../data/bb1"
    muti_process_with_apply(file_name)
    #muti_process_with_map(file_name)
    e2 = clock()
    print float(e2 - e1)
