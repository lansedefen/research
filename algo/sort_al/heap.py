import sys

class Node(object):
    def __init__(self, val):
        self.val = val
        self.next = None

def build_list():
    a1 = Node(1)
    a2 = Node(3)
    a3 = Node(5)
    a1.next = a2 
    a2.next = a3 
    b1 = Node(3.2)
    b2 = Node(33)
    b1.next = b2 
    c1 = Node(-9)
    c2 = Node(-5)
    c3 = Node(99)
    c4 = Node(5.6)
    c1.next = c2 
    c2.next = c3 
    c3.next = c4 
    return a1,b1,c1

def merge_list(k_list):
    k = len(k_list)
    print k
    tmp = []
    for i in range(0, k):
        if k_list[i].next is not None:
            tmp.append( k_list[i].val )
    while(1):

        print min(tmp)

k_list = build_list()
merge_list(k_list)
