#coding=utf8
 
from multiprocessing import Process, Queue
import os, time, random
 
# 写数据进程执行的代码:
def write(q):
 for value in range(1,1000):
  print 'Put %s to queue...' % value
  q.put(value)
  #time.sleep(random.random())
 
# 读数据进程执行的代码:
def read(q, p):
 while True:
  if not q.empty():
   value = q.get(True, timeout = 1 )
   print 'Get %s from queue.' % value
   p.put(value)
   print "size()", len(p)
   time.sleep( random.random() )
  else:
   break
 
if __name__=='__main__':
 # 父进程创建Queue，并传给各个子进程：
 q = Queue()
 p = Queue()
 pw = Process(target=write, args=(q,))
 # 启动子进程pw，写入:
 pw.start() 
 # 等待pw结束:
 pw.join()
 # 启动子进程pr，读取:
 pr_list = [Process(target=read, args=(q,p,)) for i in range(1,10)]
 for e in pr_list:
 	e.start()
 for e in pr_list:
 	e.join()
 # pr进程里是死循环，无法等待其结束，只能强行终止:
 print
 print '所有数据都写入并且读完'
