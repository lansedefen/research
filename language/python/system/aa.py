# -*- coding: utf-8 -*-
from multiprocessing import Pool, Lock
import time
from time import clock
import requests 
#from log_init import create_loger
from my_log import logger 
from mod import testLogger

def mycallback(x):
    logger.info('test main logger')
    with open('123.txt', 'a+') as f:
        f.writelines(str(x) + "\n")

def get_weibo(mid):
    url = "http://10.75.57.27/getdata/querydata2.php?condition=%s&mode=weibo&format=json" % (mid.strip())
    #try:
    if 1:
        start_time = clock()
        text = requests.get(url, timeout=4).text 
        logger.info(str(text))
        logger.debug(url)
        end_time = clock()
        testLogger()
        #lock.acquire()
        #print text
        #with open('request.log', 'a+') as logs:
        #    logs.write('request %s cost: %s\n' % (url, end_time - start_time))
        #print url
        #lock.release()
        return text  
    #except:
    #    return None

def init(l):
	global lock
	lock = l

if __name__ == '__main__':
    e1 = time.time()
    """
    data = []
    obj = open("bb1", "r")
    for line in obj:
        line = line.strip()
        line = line.split("\t")[1]
        data.append(line)
    obj.close()
    """

    lock = Lock()
    pool = Pool(10, initializer = init, initargs=(lock,) )
    #pool.map(get_weibo, data)
    #pool.map_async(get_weibo, data, callback=mycallback)

    obj = open("bb1", "r")
    for line in obj:
        line = line.strip()
        line = line.split("\t")[1]
        #get_weibo(line, lock)
        print line
        #pool.apply_async(get_weibo, (line, ))
        pool.apply_async(get_weibo, (line, ), callback = mycallback)
    pool.close()
    pool.join()
    e2 = time.time()
    print float(e2 - e1)
