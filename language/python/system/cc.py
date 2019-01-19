import os
import multiprocessing
import time
 
def  showdata(lock,i):
    with lock:
        time.sleep(0.1)
        print(i)
 
 
if __name__=="__main__":
    lock=multiprocessing.RLock()  
    for num in range(10):
        multiprocessing.Process(target=showdata,args=(lock,num)).start()
