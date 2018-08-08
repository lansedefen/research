#!/usr/bin/python 
# encoding: UTF-8

import threading
import time

def produce():
    global product
    if con.acquire():
        while True:
            if product is None:
                print 'produce...'
                product = 'anything'
                con.notify()
            con.wait()
            time.sleep(2)
def consume():
    global product
    if con.acquire():
        while True:
            if product is not None:
                print 'consume...'
                product = None
                con.notify()
            con.wait()
            time.sleep(2)
product = None
con = threading.Condition()
t1 = threading.Thread(target=produce)
t2 = threading.Thread(target=consume)
t1.start()
t2.start()
