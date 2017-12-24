import multiprocessing
import time

def worker_with_queue(q, out_q):
	while 1:
		try:
		   line = q.get(block = True, timeout = 1)
		   element = "111111111111" * 10
		   print element
		   out_q.put( element )
		except:
		   print "exit"
		   out_q.cancel_join_thread()
		   q.task_done()
		   return -1

def work_with_queue():
	q = multiprocessing.JoinableQueue()
	out_q = multiprocessing.Queue()
	for line in range(1,10000):
		line = "zhonggggggggggggggggggggg"* 10000
		q.put(line, block = False)

	pre_arr = [ multiprocessing.Process(target = worker_with_queue, args = (q,out_q,)) for i in range(0, 10)]
	for i in pre_arr:
	   i.start()
	for i in pre_arr:
	   i.join()
	print "********"

if __name__ == "__main__":
	work_with_queue()
