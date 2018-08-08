import Queue
import threading,time,random
import time

class consumer( threading.Thread ): 
    def __init__(self,que): 
        threading.Thread.__init__(self) 
        #self.daemon = True
        self.queue = que 

    def run(self): 
        while True: 
            if self.queue.empty(): 
		time.sleep(0.5)
		continue
            item = self.queue.get() 
            time.sleep(0.5) 
            print self.name, ":", item 
            #self.queue.task_done() 
        return 

def work_with_queue():
	que = Queue.Queue()
	consumers = [ consumer(que) for x in range(5) ]
	for c in consumers: 
		c.daemon = True
		c.start() 

	print 1111
	count = 0
	while 1:
		count +=1
		que.put(count, block = False)
	#for c in consumers:
	#	c.join()

if __name__ == "__main__":
	work_with_queue()
